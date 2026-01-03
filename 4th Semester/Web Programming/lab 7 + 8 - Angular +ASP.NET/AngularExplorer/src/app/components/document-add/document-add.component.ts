import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { Router } from '@angular/router';
import { DocumentFormComponent } from '../document-form/document-form.component';
import { DocumentService } from '../../document.service';
import { Document } from '../../models/document.model';

@Component({
  selector: 'app-document-add',
  standalone: true,
  imports: [CommonModule, DocumentFormComponent],
  template: `
    <div class="container mt-4">
      <h2>Add New Document</h2>
      <app-document-form
        [submitButtonText]="'Add Document'"
        (formSubmit)="onFormSubmit($event)"
        (cancelAction)="onCancel()">
      </app-document-form>
    </div>
  `,
  styles: []
})
export class DocumentAddComponent {

  constructor(
    private documentService: DocumentService,
    private router: Router
  ) {}

  onFormSubmit(document: Document): void {
    this.documentService.create(document).subscribe({
      next: () => {
        this.router.navigate(['/documents']);
      },
      error: (err) => {
        console.error('Error creating document:', err);
      }
    });
  }

  onCancel(): void {
    this.router.navigate(['/documents']);
  }
}
