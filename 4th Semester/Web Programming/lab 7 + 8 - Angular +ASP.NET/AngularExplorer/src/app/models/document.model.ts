// document.model.ts - Update to match C# model naming conventions
export interface Document {
  id: number; // Make optional for new documents
  title: string;
  author: string;
  pages: number;
  type: string;
  format: string;
  userId: number;
  createdAt?: Date; // Changed from created_at to camelCase
  updatedAt?: Date; // Changed from updated_at to camelCase
}
