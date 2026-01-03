import { Component, EventEmitter, Input, OnInit, Output } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormBuilder, FormGroup, ReactiveFormsModule, Validators } from '@angular/forms';
import { Document } from '../../models/document.model';

@Component({
  selector: 'app-document-form',
  standalone: true,
  imports: [CommonModule, ReactiveFormsModule],
  templateUrl: './document-form.component.html',
  styleUrl: './document-form.component.css'
})
export class DocumentFormComponent implements OnInit {
  @Input() document: Document | null = null;
  @Input() submitButtonText = 'Save';
  @Output() formSubmit = new EventEmitter<Document>();
  @Output() cancelAction = new EventEmitter<void>();

  documentForm!: FormGroup;
  isSubmitting = false;

  constructor(private fb: FormBuilder) {}


  ngOnInit(): void {
    this.initForm();

    if (this.document) {
      this.documentForm.patchValue(this.document);
    }
  }

  initForm(): void {
    this.documentForm = this.fb.group({
      title: ['', [Validators.required, Validators.minLength(3)]],
      author: ['', Validators.required],
      pages: [0, [Validators.required, Validators.min(1)]],
      type: ['', Validators.required],
      format: ['', Validators.required]
    });
  }

  onSubmit(): void {
    if (this.documentForm.invalid) {
      this.documentForm.markAllAsTouched();
      return;
    }

    this.isSubmitting = true;

    const documentData: Partial<Document> = {
      title: this.documentForm.get('title')?.value,
      author: this.documentForm.get('author')?.value,
      pages: this.documentForm.get('pages')?.value,
      type: this.documentForm.get('type')?.value,
      format: this.documentForm.get('format')?.value,
    };

    if (this.document?.id) {
      documentData.id = this.document.id;
    }

    this.formSubmit.emit(documentData as Document);
  }
  onCancel(): void {
    this.cancelAction.emit();
  }
}
