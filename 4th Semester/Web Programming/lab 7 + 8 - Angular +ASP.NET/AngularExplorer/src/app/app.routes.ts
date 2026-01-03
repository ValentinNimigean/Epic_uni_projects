import { Routes } from '@angular/router';
import { authGuard } from './guards/auth.guard';

export const routes: Routes = [

  {
    path: 'login',
    loadComponent: () => import('./components/login/login.component').then(m => m.LoginComponent)
  },
  {
    path: 'register',
    loadComponent: () => import('./components/register/register.component').then(m => m.RegisterComponent)
  },


  {
    path: 'home',
    loadComponent: () => import('./components/home/home.component').then(m => m.HomeComponent),
    canActivate: [authGuard]
  },
  {
    path: 'documents',
    loadComponent: () => import('./components/document-list/document-list.component').then(m => m.DocumentListComponent),
    canActivate: [authGuard]
  },
  {
    path: 'document/add',
    loadComponent: () => import('./components/document-add/document-add.component').then(m => m.DocumentAddComponent),
    canActivate: [authGuard]
  },
  {path: 'document/:id',
    loadComponent: () => import('./components/document-detail/document-detail.component').then(m => m.DocumentDetailComponent),
    canActivate :[authGuard]
  },
  {path: 'document/:id/edit',
  loadComponent: () => import('./components/document-edit/document-edit.component').then(m => m.DocumentEditComponent),
  canActivate: [authGuard]  },

  // Redirect empty path to login
  {
    path: '',
    redirectTo: '/home',
    pathMatch: 'full'
  },

  // Redirect unknown paths to login
  {
    path: '**',
    redirectTo: '/home'
  }
];
