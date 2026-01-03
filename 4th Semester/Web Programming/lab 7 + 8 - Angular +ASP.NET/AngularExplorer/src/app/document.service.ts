import { Injectable, PLATFORM_ID, inject } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { catchError, Observable, tap, throwError } from 'rxjs';
import { isPlatformBrowser } from '@angular/common';
import { Document } from './models/document.model';
import { AuthService } from './service/auth.service';

@Injectable({
  providedIn: 'root'
})
export class DocumentService {
  private apiUrl = 'http://localhost:5000/api';
  private platformId = inject(PLATFORM_ID);

  constructor(
    private http: HttpClient,
    private authService: AuthService
  ) {
    console.log('DocumentService initialized');
  }

  private getHeaders(): HttpHeaders {
    return new HttpHeaders().set('Content-Type', 'application/json');
  }

  private getOptions() {
    return {
      headers: this.getHeaders(),
      withCredentials: true // This is crucial for cookie-based auth
    };
  }

  getAll(): Observable<Document[]> {
    console.log('DocumentService: Fetching all documents');
    return this.http.get<Document[]>(`${this.apiUrl}/documents`, this.getOptions())
      .pipe(
        tap({
          next: data => console.log('Documents fetched successfully', data),
          error: error => console.error('Error fetching documents', error)
        })
      );
  }

  getById(id: number): Observable<Document> {
    return this.http.get<Document>(`${this.apiUrl}/documents/${id}`, this.getOptions())
      .pipe(
        tap({
          next: data => console.log(`Document ${id} fetched successfully`, data),
          error: error => console.error(`Error fetching document ${id}`, error)
        })
      );
  }

  create(document: Partial<Document>): Observable<Document> {
    // Only send the fields that the backend expects
    const documentToSend = {
      title: document.title,
      author: document.author,
      pages: document.pages,
      type: document.type,
      format: document.format
    };

    console.log('Creating document:', documentToSend);
    return this.http.post<Document>(`${this.apiUrl}/documents`, documentToSend, this.getOptions())
      .pipe(
        tap({
          next: data => console.log('Document created successfully', data),
          error: error => console.error('Error creating document', error)
        })
      );
  }

  update(id: number, document: Document): Observable<any> {
    // Ensure we only send the fields expected by the API
    const payload = {
      Id: id,
      Title: document.title,
      Author: document.author,
      Pages: document.pages,
      Type: document.type,
      Format: document.format
    };

    console.log('Sending payload:', payload);

    return this.http.put<any>(`${this.apiUrl}/documents/${id}`, payload, this.getOptions())
      .pipe(
        tap(() => console.log('Document updated successfully')),
        catchError(error => {
          console.error('Update error:', error.error);
          return throwError(() => error);
        })
      );
  }

  delete(id: number): Observable<any> {
    console.log(`Attempting to delete document ${id}`);
    return this.http.delete<any>(`${this.apiUrl}/documents/${id}`, this.getOptions())
      .pipe(
        tap({
          next: data => console.log(`Document ${id} deleted successfully`, data),
          error: error => console.error(`Error deleting document ${id}`, error)
        })
      );
  }
}
