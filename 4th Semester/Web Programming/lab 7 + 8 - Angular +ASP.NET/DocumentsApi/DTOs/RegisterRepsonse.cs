namespace DocumentsApi.Dtos
{
  
    public class RegisterResponse
    {
        public int Id { get; set; }
        public string Email { get; set; } = null!;
        public string Username { get; set; } = null!;
        public string Message { get; set; } = null!;
    }


   
}
