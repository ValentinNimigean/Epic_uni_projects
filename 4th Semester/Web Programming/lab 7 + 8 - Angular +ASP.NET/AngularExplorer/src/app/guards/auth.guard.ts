import { Injectable } from '@angular/core';
import { CanActivate, ActivatedRouteSnapshot, RouterStateSnapshot, Router } from '@angular/router';
import { Observable, lastValueFrom } from 'rxjs';
import { AuthService } from '../service/auth.service';

@Injectable({
  providedIn: 'root'
})
export class authGuard implements CanActivate {
  constructor(private authService: AuthService, private router: Router) {}

  async canActivate(
    route: ActivatedRouteSnapshot,
    state: RouterStateSnapshot
  ): Promise<boolean> {
    console.log('AuthGuard: Checking authentication...');

    try {
      // Check if already authenticated first
      if (this.authService.isAuthenticated()) {
        return true;
      }

      // Otherwise verify with backend
      const isAuthenticated = await lastValueFrom(this.authService.checkAuthStatus());

      if (!isAuthenticated) {
        // This redirects to Angular route, not API endpoint
        this.router.navigate(['/login'], {
          queryParams: { returnUrl: state.url }
        });
        return false;
      }

      return true;
    } catch (error) {
      console.error('AuthGuard: Authentication check failed', error);
      this.router.navigate(['/login']);
      return false;
    }
  }
}
