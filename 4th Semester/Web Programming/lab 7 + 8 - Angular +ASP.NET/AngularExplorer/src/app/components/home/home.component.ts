// src/app/components/home/home.component.ts
import { Component } from '@angular/core';
import { RouterModule } from '@angular/router';

@Component({
  selector: 'app-home',
  standalone: true,
  imports: [RouterModule],
  template: `
    <div class="container mt-5">
      <div class="jumbotron">
        <h1 class="display-4">Angular Explorer</h1>
        <p class="lead">A simple application to manage your documents</p>
        <hr class="my-4">
        <p>Use this application to create, view, edit, and delete your documents.</p>

      </div>
    </div>
  `
})
export class HomeComponent {}
