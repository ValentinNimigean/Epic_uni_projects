using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using DocumentsApi.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.EntityFrameworkCore;
using DocumentsApi.Data;
using System.Security.Claims;
using DocumentsApi.DTOs;

[Route("api/[controller]")]
[ApiController]
[Authorize]
public class DocumentsController : ControllerBase
{
    private readonly AppDbContext _context;
    private readonly ILogger<DocumentsController> _logger;

    public DocumentsController(AppDbContext context, ILogger<DocumentsController> logger)
    {
        _context = context;
        _logger = logger;
    }

    [HttpGet]
    public async Task<ActionResult<IEnumerable<Document>>> GetAllDocuments()
    {
        var userIdClaim = User.FindFirst(ClaimTypes.NameIdentifier);
        if (userIdClaim != null && int.TryParse(userIdClaim.Value, out int userId))
        {
            return await _context.Documents
                .Where(d => d.UserId == userId)
                .Include(d => d.User)
                .ToListAsync();
        }

        return BadRequest("Invalid user ID.");
    }

    [HttpPost]
    public async Task<ActionResult<Document>> CreateDocument([FromBody] DocumentCreate dto)
    {
        if (!ModelState.IsValid)
            return BadRequest(ModelState);

        var userIdClaim = User.FindFirst(ClaimTypes.NameIdentifier);
        if (userIdClaim != null && int.TryParse(userIdClaim.Value, out int userId))
        {
            try
            {
                var document = new Document
                {
                    Title = dto.Title,
                    Author = dto.Author,
                    Pages = dto.Pages,
                    Type = dto.Type,
                    Format = dto.Format,
                    UserId = userId,
                    CreatedAt = DateTime.UtcNow,
                    UpdatedAt = DateTime.UtcNow,
                    User = null // <-- Defensive: ensure no navigation property is set
                };

                _context.Documents.Add(document);
                await _context.SaveChangesAsync();

                return CreatedAtAction(nameof(GetDocumentById), new { id = document.Id }, document);
            }
            catch (Exception ex)
            {
                _logger.LogError(ex, "Error creating document");
                return StatusCode(500, "An error occurred while creating the document.");
            }
        }

        return BadRequest("Invalid user ID.");
    }

    [HttpPut("{id}")]
    public async Task<IActionResult> UpdateDocument(int id, [FromBody] DocumentCreate dto)
    {
        var userIdClaim = User.FindFirst(ClaimTypes.NameIdentifier);
        if (userIdClaim == null || !int.TryParse(userIdClaim.Value, out int userId))
        {
            return BadRequest("Invalid user ID.");
        }

        var existingDocument = await _context.Documents
            .FirstOrDefaultAsync(d => d.Id == id && d.UserId == userId);

        if (existingDocument == null)
        {
            return NotFound();
        }

        existingDocument.Title = dto.Title;
        existingDocument.Author = dto.Author;
        existingDocument.Pages = dto.Pages;
        existingDocument.Type = dto.Type;
        existingDocument.Format = dto.Format;
        existingDocument.UpdatedAt = DateTime.UtcNow;

        try
        {
            await _context.SaveChangesAsync();
            return NoContent();
        }
        catch (Exception ex)
        {
            _logger.LogError(ex, "Error updating document");
            return StatusCode(500, $"Error updating document: {ex.Message}");
        }
    }

    [HttpGet("{id}")]
    public async Task<ActionResult<Document>> GetDocumentById(int id)
    {
        var userIdClaim = User.FindFirst(ClaimTypes.NameIdentifier);
        if (userIdClaim != null && int.TryParse(userIdClaim.Value, out int userId))
        {
            var document = await _context.Documents
                .Include(d => d.User)
                .FirstOrDefaultAsync(d => d.Id == id && d.UserId == userId);

            if (document == null)
            {
                return NotFound();
            }

            return Ok(document);
        }

        return BadRequest("Invalid user ID.");
    }

    [HttpDelete("{id}")]
    public async Task<IActionResult> DeleteDocument(int id)
    {
        var userIdClaim = User.FindFirst(ClaimTypes.NameIdentifier);
        if (userIdClaim == null || !int.TryParse(userIdClaim.Value, out int userId))
        {
            return BadRequest("Invalid user ID.");
        }

        var document = await _context.Documents.FirstOrDefaultAsync(d => d.Id == id && d.UserId == userId);
        if (document == null)
        {
            return NotFound();
        }

        _context.Documents.Remove(document);
        await _context.SaveChangesAsync();

        return NoContent();
    }
}