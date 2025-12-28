using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text.Json.Serialization;

namespace DocumentsApi.Models
{
    public class User
    {
        [Key]
        public int Id { get; set; }

        [Required]
        public string Email { get; set; }

        [Required]
        public string Username { get; set; }

        [Required]
        public string Password { get; set; }

        public ICollection<Document> Documents { get; set; }


        
        public User()
        {
            Email = string.Empty;
            Username = string.Empty;
            Password = string.Empty;
            Documents = new List<Document>();
        }
    }
}
