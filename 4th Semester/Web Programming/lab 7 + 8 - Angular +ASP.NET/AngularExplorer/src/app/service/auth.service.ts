import { Injectable, PLATFORM_ID, inject } from '@angular/core';
import { HttpClient, HttpHeaders, HttpContext, HttpContextToken } from '@angular/common/http';
import { BehaviorSubject, Observable, tap, catchError, throwError, of } from 'rxjs';
import { Router } from '@angular/router';
import { isPlatformBrowser } from '@angular/common';
import { timeout, finalize, map } from 'rxjs/operators';

export class TimeoutErrorHandler {
  static readonly TIMEOUT_REQUEST = new HttpContextToken(() => 30000);
}

interface LoginCredentials {
  username: string;
  password: string;
}

interface RegisterCredentials {
  username: string;
  password: string;
  email?: string;
}

interface AuthResponse {
  id: number;
  email: string;
  username: string;
}

@Injectable({
  providedIn: 'root'
})
export class AuthService {
  private apiUrl = 'http://localhost:5000/api/auth';
  private isAuthenticatedSubject = new BehaviorSubject<boolean>(false);
  private usernameSubject = new BehaviorSubject<string>('');
  private authCheckInProgress = false;

  public isAuthenticated$ = this.isAuthenticatedSubject.asObservable();
  public isLoggedIn$ = this.isAuthenticated$;
  public username$ = this.usernameSubject.asObservable();
  private platformId = inject(PLATFORM_ID);

  constructor(
    private http: HttpClient,
    private router: Router
  ) {
    // Initial check on service initialization
    if (isPlatformBrowser(this.platformId)) {
      this.checkAuthStatus().subscribe({
        next: (isAuthenticated) => {
          console.log('Initial auth check result:', isAuthenticated);
        },
        error: (err) => {
          console.error('Initial auth check failed:', err);
        }
      });
    }
  }
  // In your AuthService, modify the checkAuthStatus method:

  checkAuthStatus(): Observable<boolean> {
    if (!isPlatformBrowser(this.platformId)) {
      this.isAuthenticatedSubject.next(false);
      return of(false);
    }

    if (this.authCheckInProgress) {
      return this.isAuthenticated$;
    }

    this.authCheckInProgress = true;

    return this.http.get<AuthResponse>(`${this.apiUrl}/me`, {
      withCredentials: true
      // Removed cache-control headers that cause CORS issues
    }).pipe(
      map(user => {
        this.isAuthenticatedSubject.next(true);
        if (user.username) {
          this.usernameSubject.next(user.username);
        }
        return true;
      }),
      catchError(error => {
        console.error('Auth verification failed:', error);
        this.isAuthenticatedSubject.next(false);
        this.usernameSubject.next('');
        return of(false);
      }),
      finalize(() => {
        this.authCheckInProgress = false;
      })
    );
  }



  login(credentials: LoginCredentials): Observable<AuthResponse> {
    console.log('Login attempt started:', credentials.username);

    return this.http.post<AuthResponse>(
      `${this.apiUrl}/login`,
      credentials,
      {
        withCredentials: true,
        context: new HttpContext().set(TimeoutErrorHandler.TIMEOUT_REQUEST, 10000)
      }
    ).pipe(
      timeout(10000),
      tap(response => {
        console.log('Login successful:', response);
        this.isAuthenticatedSubject.next(true);
        if (response.username) {
          this.usernameSubject.next(response.username);
        }
      }),
      catchError(error => {
        console.error('Login error:', error);
        this.isAuthenticatedSubject.next(false);
        return throwError(() => new Error(error.message || 'Login failed'));
      }),
      finalize(() => console.log('Login attempt completed'))
    );
  }

  logout(): Observable<any> {
    return this.http.post(`${this.apiUrl}/logout`, {}, { withCredentials: true })
      .pipe(
        tap(() => {
          this.clearAuthState();
        }),
        catchError(error => {
          this.clearAuthState();
          return throwError(() => error);
        })
      );
  }

  private clearAuthState(): void {
    this.isAuthenticatedSubject.next(false);
    this.usernameSubject.next('');
    this.router.navigate(['/login']);
  }

  register(credentials: RegisterCredentials): Observable<AuthResponse> {
    return this.http.post<AuthResponse>(`${this.apiUrl}/register`, credentials, { withCredentials: true })
      .pipe(
        catchError(error => {
          console.error('Registration failed:', error);
          return throwError(() => error);
        })
      );
  }

  isAuthenticated(): boolean {
    return this.isAuthenticatedSubject.value;
  }
}
