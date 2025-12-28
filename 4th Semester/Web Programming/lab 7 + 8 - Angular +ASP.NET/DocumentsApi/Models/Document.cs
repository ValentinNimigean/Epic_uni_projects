using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Text.Json.Serialization;

namespace DocumentsApi.Models
{
    public class Document
    {
        [Key]
        public int Id { get; set; }

        [Required]
        public string Title { get; set; }

        [Required]
        public string Author { get; set; }

        public int Pages { get; set; }

        [Required]
        public string Type { get; set; }

        [Required]
        public string Format { get; set; }

        public DateTime CreatedAt { get; set; }
        public DateTime UpdatedAt { get; set; }
        public string Publisher { get; set; }


        [ForeignKey("UserId")]
        public int UserId { get; set; }





        [JsonIgnore]
        public User User { get; set; }

        public Document()
        {
            Title = string.Empty;
            Author = string.Empty;
            Type = string.Empty;
            Format = string.Empty;
            User = new User(); // Prevent null warnings, can be overwritten by EF
            CreatedAt = DateTime.UtcNow;
            UpdatedAt = DateTime.UtcNow;
        }
    }
}
