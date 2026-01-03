import { Component, OnInit, Inject, PLATFORM_ID } from '@angular/core';
import { CommonModule, isPlatformBrowser } from '@angular/common';
import { RouterLink } from '@angular/router';
import { FormsModule } from '@angular/forms';
import { DocumentService } from '../../document.service';
import { Document } from '../../models/document.model';
interface FilterState {
  type: string;
  format: string;
  timestamp: Date;
}

@Component({
  selector: 'app-document-list',
  standalone: true,
  imports: [CommonModule, RouterLink, FormsModule],
  templateUrl: './document-list.component.html',
  styleUrls: ['./document-list.component.css']
})
export class DocumentListComponent implements OnInit {
  documents: Document[] = [];
  filteredDocuments: Document[] = [];
  loading = true;
  error: string | null = null;


  typeFilter: string = '';
  formatFilter: string = '';
  availableTypes: string[] = [];
  availableFormats: string[] = [];


  previousFilter: FilterState | null = null;


  lastAppliedType: string = '';
  lastAppliedFormat: string = '';

  private isBrowser: boolean;

  constructor(
    private documentService: DocumentService,
    @Inject(PLATFORM_ID) private platformId: Object
  ) {
    this.isBrowser = isPlatformBrowser(this.platformId);
  }

  ngOnInit(): void {
    this.loadDocuments();
    this.loadFilterHistory();
  }

  loadDocuments(): void {
    this.loading = true;
    this.documentService.getAll().subscribe({
      next: (documents) => {
        this.documents = documents;
        this.extractFilterOptions();
        this.applyFilters(false);
        this.loading = false;
      },
      error: (err) => {
        this.error = 'Failed to load documents: ' + (err.error?.message || err.message);
        this.loading = false;
      }
    });
  }

  extractFilterOptions(): void {
    this.availableTypes = [...new Set(this.documents.map(doc => doc.type))].filter(Boolean);
    this.availableFormats = [...new Set(this.documents.map(doc => doc.format))].filter(Boolean);
  }

  applyFilters(trackHistory: boolean = true): void {

    if (trackHistory && (this.lastAppliedType !== this.typeFilter || this.lastAppliedFormat !== this.formatFilter)) {

      this.previousFilter = {
        type: this.lastAppliedType,
        format: this.lastAppliedFormat,
        timestamp: new Date()
      };


      if (this.isBrowser && (this.previousFilter.type || this.previousFilter.format)) {
        localStorage.setItem('documentPreviousFilter', JSON.stringify(this.previousFilter));
      }


      this.lastAppliedType = this.typeFilter;
      this.lastAppliedFormat = this.formatFilter;
    }

    this.filteredDocuments = this.documents.filter(doc => {
      const matchesType = !this.typeFilter || doc.type === this.typeFilter;
      const matchesFormat = !this.formatFilter || doc.format === this.formatFilter;
      return matchesType && matchesFormat;
    });
  }

  clearFilters(): void {

    if (this.typeFilter || this.formatFilter) {
      this.previousFilter = {
        type: this.typeFilter,
        format: this.formatFilter,
        timestamp: new Date()
      };

      if (this.isBrowser) {
        localStorage.setItem('documentPreviousFilter', JSON.stringify(this.previousFilter));
      }


      this.lastAppliedType = '';
      this.lastAppliedFormat = '';
    }

    this.typeFilter = '';
    this.formatFilter = '';
    this.applyFilters(false);
  }

  loadFilterHistory(): void {
    if (!this.isBrowser) return;

    const prevFilterStr = localStorage.getItem('documentPreviousFilter');
    if (prevFilterStr) {
      try {
        const savedFilter = JSON.parse(prevFilterStr);
        this.previousFilter = {
          ...savedFilter,
          timestamp: new Date(savedFilter.timestamp)
        };
      } catch (e) {
        console.error('Error loading previous filter', e);
        this.previousFilter = null;
      }
    }
    this.lastAppliedType = this.typeFilter;
    this.lastAppliedFormat = this.formatFilter;
  }

  applyPreviousFilter(): void {
    if (!this.previousFilter) return;

    const tempType = this.typeFilter;
    const tempFormat = this.formatFilter;

    this.typeFilter = this.previousFilter.type;
    this.formatFilter = this.previousFilter.format;

    this.lastAppliedType = this.previousFilter.type;
    this.lastAppliedFormat = this.previousFilter.format;

    this.previousFilter = {
      type: tempType,
      format: tempFormat,
      timestamp: new Date()
    };

    if (this.isBrowser) {
      localStorage.setItem('documentPreviousFilter', JSON.stringify(this.previousFilter));
    }

    this.applyFilters(false);


  }

  deleteDocument(documentId: number): void {
    if (!documentId || !confirm('Are you sure you want to delete this document?')) {
      return;
    }

    this.documentService.delete(documentId).subscribe({
      next: () => {
        // Refresh the document list after deletion
        this.loadDocuments();
      },
      error: (err) => {
        this.error = 'Failed to delete document';
        console.error('Error deleting document:', err);
      }
    });
  }
}
