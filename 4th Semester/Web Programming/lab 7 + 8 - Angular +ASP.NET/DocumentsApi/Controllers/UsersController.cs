using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using DocumentsApi.Models;
using Microsoft.AspNetCore.Authorization;
using DocumentsApi.Data;

using Microsoft.EntityFrameworkCore;


[Route("api/[controller]")]
[ApiController]
[Authorize]
public class UsersController : ControllerBase
{
    private readonly AppDbContext _context;
    public UsersController(AppDbContext context) => _context = context;

    [HttpGet]
    public async Task<ActionResult<IEnumerable<User>>> GetUsers() =>
        await _context.Users.Include(u => u.Documents).ToListAsync();

    [HttpPost]
    public async Task<ActionResult<User>> CreateUser(User user)
    {
        _context.Users.Add(user);
        await _context.SaveChangesAsync();
        return CreatedAtAction(nameof(GetUsers), new { id = user.Id }, user);
    }
}
