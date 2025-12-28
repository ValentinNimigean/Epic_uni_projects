namespace DocumentsApi.Dtos
{
    public class LoginResponse
    {
        public int Id { get; set; }
        public string Email { get; set; } = string.Empty;
        public string Username { get; set; } = string.Empty;
        public string Message { get; set; } = "Login successful";
    }
}
