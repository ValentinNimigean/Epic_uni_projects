namespace DocumentsApi.DTOs
{
    public class DocumentCreate
    {
        public required string Title { get; set; }
        public required string Author { get; set; }
        public int Pages { get; set; }
        public required string Type { get; set; }
        public required string Format { get; set; }
    }
}