import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ActivatedRoute, Router } from '@angular/router';
import { DocumentFormComponent } from '../document-form/document-form.component';
import { DocumentService} from '../../document.service';
import { catchError, of } from 'rxjs';
import { Document } from '../../models/document.model';

@Component({
  selector: 'app-document-edit',
  standalone: true,
  imports: [CommonModule, DocumentFormComponent],
  template: `
    <div class="container mt-4">
      <h2>Edit Document</h2>

      <div *ngIf="loading" class="alert alert-info">
        Loading document...
      </div>

      <div *ngIf="error" class="alert alert-danger">
        {{ error }}
      </div>

      <app-document-form
        *ngIf="!loading && document"
        [document]="document"
        submitButtonText="Update"
        (formSubmit)="onFormSubmit($event)"
        (cancelAction)="onCancel()">
      </app-document-form>
    </div>
  `,
  styles: []
})
export class DocumentEditComponent implements OnInit {
  document: Document | null = null;
  loading = true;
  error: string | null = null;

  constructor(
    private route: ActivatedRoute,
    private router: Router,
    private documentService: DocumentService
  ) {}

  ngOnInit(): void {
    const id = Number(this.route.snapshot.paramMap.get('id'));
    if (!id) {
      this.error = 'Invalid document ID';
      this.loading = false;
      return;
    }

    this.documentService.getById(id).pipe(
      catchError(err => {
        this.error = `Failed to load document: ${err.message}`;
        this.loading = false;
        return of(null);
      })
    ).subscribe(document => {
      this.document = document;
      this.loading = false;
    });
  }

  // document-edit.component.ts
  onFormSubmit(updatedDocument: Document): void {
    if (!this.document?.id) return;

    // Make sure all required fields are included
    const documentToUpdate = {
      ...updatedDocument,
      id: this.document.id
    };

    this.documentService.update(this.document.id, documentToUpdate).subscribe({
      next: () => {
        this.router.navigate(['/documents']);
      },
      error: err => {
        console.error('Error updating document', err);
        this.error = `Failed to update document: ${err.message}`;
      }
    });
  }

  onCancel(): void {
    this.router.navigate(['/documents']);
  }
}
