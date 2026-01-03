import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { ActivatedRoute, Router, RouterModule } from '@angular/router';
import { DocumentService} from '../../document.service';
import {Document} from '../../models/document.model';

@Component({
  selector: 'app-document-detail',
  standalone: true,
  imports: [CommonModule, RouterModule],
  styleUrls: ['./document-detail.component.css'],

  template: `
    <div class="detail-container mt-5">
      <!-- Loading State -->
      <div *ngIf="loading" class="loading-spinner">
        <div class="spinner-border text-primary" role="status">
          <span class="visually-hidden">Loading...</span>
        </div>
      </div>

      <!-- Error State -->
      <div *ngIf="error" class="alert alert-danger">
        {{ error }}
      </div>

      <!-- Document Details -->
      <div *ngIf="!loading && document">
        <!-- Header -->
        <div class="detail-header">
          <h1>{{ document.title }}</h1>
          <div class="meta-info">
            <span>By {{ document.author }}</span> •
            <span>{{ document.pages }} pages</span>
          </div>
        </div>

        <!-- Details Card -->
        <div class="detail-card card">
          <div class="card-header">
            <h5 class="mb-0">Document Information</h5>
          </div>
          <div class="card-body">
            <div class="row">
              <div class="col-md-6">
                <div>
                  <div class="field-label">Document Type</div>
                  <div class="field-value">
                    <span class="document-badge badge-type">{{ document.type }}</span>
                  </div>
                </div>

                <div>
                  <div class="field-label">Format</div>
                  <div class="field-value">
                    <span class="document-badge badge-format">{{ document.format }}</span>
                  </div>
                </div>
              </div>

              <div class="col-md-6">
                <div>
                  <div class="field-label">Author</div>
                  <div class="field-value">{{ document.author }}</div>
                </div>

                <div>
                  <div class="field-label">Pages</div>
                  <div class="field-value">{{ document.pages }}</div>
                </div>
              </div>
            </div>

            <div class="timestamp-section">
              <div class="row">
                <div class="col-md-6">
                  <strong>Created:</strong> {{ document.createdAt | date:'medium' }}
                </div>
                <div class="col-md-6">
                  <strong>Last Updated:</strong> {{ document.updatedAt | date:'medium' }}
                </div>
              </div>
            </div>
          </div>
        </div>

        <!-- Action Buttons -->
        <div class="action-buttons">
          <a routerLink="/documents" class="btn btn-back">
            <i class="bi bi-arrow-left me-1"></i> Back to Documents
          </a>
          <a [routerLink]="['/document', document.id,'edit']" class="btn btn-edit">
            <i class="bi bi-pencil me-1"></i> Edit Document
          </a>
          <button class="btn btn-delete" (click)="deleteDocument()">
            <i class="bi bi-trash me-1"></i> Delete Document
          </button>
        </div>
      </div>
    </div>
  `
})

export class DocumentDetailComponent implements OnInit {
  document: Document | null = null;
  loading = true;
  error: string | null = null;

  constructor(
    private documentService: DocumentService,
    private route: ActivatedRoute,
    private router: Router
  ) {}

  ngOnInit(): void {
    this.loadDocument();
  }

  loadDocument(): void {
    const id = Number(this.route.snapshot.paramMap.get('id'));
    if (!id) {
      this.error = 'Invalid document ID';
      this.loading = false;
      return;
    }

    this.documentService.getById(id).subscribe({
      next: (data) => {
        this.document = data;
        this.loading = false;
      },
      error: (err) => {
        this.error = 'Failed to load document details';
        this.loading = false;
        console.error('Error fetching document:', err);
      }
    });
  }

  deleteDocument(): void {
    if (!this.document || !confirm('Are you sure you want to delete this document?')) {
      return;
    }

    this.documentService.delete(this.document.id).subscribe({
      next: () => {
        this.router.navigate(['/documents']);
      },
      error: (err) => {
        this.error = 'Failed to delete document';
        console.error('Error deleting document:', err);
      }
    });
  }
}
