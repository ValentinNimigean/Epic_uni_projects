// header.component.ts
import { Component, OnInit, PLATFORM_ID, inject, OnDestroy } from '@angular/core';
import { RouterModule, Router, NavigationEnd } from '@angular/router';
import { CommonModule, isPlatformBrowser } from '@angular/common';
import { filter } from 'rxjs/operators';
import { AuthService } from '../../service/auth.service';
import { Observable, Subscription } from 'rxjs';

@Component({
  selector: 'app-header',
  standalone: true,
  imports: [RouterModule, CommonModule],
  templateUrl: './header.component.html',
  styleUrl: './header.component.css'
})
export class HeaderComponent implements OnInit, OnDestroy {
  private platformId = inject(PLATFORM_ID);
  title = 'Angular Explorer';
  isAuthPage = false;
  isLoggedIn$!: Observable<boolean>;
  username: string = '';
  private usernameSubscription!: Subscription;

  constructor(private router: Router, private authService: AuthService) {}

  ngOnInit() {
    this.isLoggedIn$ = this.authService.isAuthenticated$;
    this.checkIfAuthPage(this.router.url);

    // Subscribe to username changes
    this.usernameSubscription = this.authService.username$.subscribe(username => {
      this.username = username;
    });

    this.router.events.pipe(
      filter(event => event instanceof NavigationEnd)
    ).subscribe((event: any) => {
      this.checkIfAuthPage(event.url);
    });
  }

  ngOnDestroy() {
    if (this.usernameSubscription) {
      this.usernameSubscription.unsubscribe();
    }
  }

  private checkIfAuthPage(url: string) {
    this.isAuthPage = url.includes('/login') || url.includes('/register');
  }

  logout() {
    this.authService.logout();
    if (isPlatformBrowser(this.platformId)) {
      localStorage.removeItem('username');
    }
    this.router.navigate(['login']);
  }
}
