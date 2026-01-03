import { HttpInterceptorFn } from '@angular/common/http';
import { isPlatformBrowser } from '@angular/common';
import { PLATFORM_ID, inject } from '@angular/core';
import { Router } from '@angular/router';
import { catchError } from 'rxjs/operators';
import { throwError } from 'rxjs';

export const authInterceptor: HttpInterceptorFn = (req, next) => {
  const platformId = inject(PLATFORM_ID);
  const router = inject(Router);

  // For cookie-based authentication, we just need withCredentials
  // No need to manually add Authorization headers
  if (isPlatformBrowser(platformId)) {
    req = req.clone({
      withCredentials: true
    });
  }

  return next(req).pipe(
    catchError(error => {
      console.error('HTTP request failed:', error);

      if (error.status === 401 ||
        (error.status === 404 && error.url?.includes('/auth/login'))) {
        console.log('Not authenticated, redirecting to login');
        router.navigate(['/login']);
      }

      return throwError(() => error);
    })
  );
};
