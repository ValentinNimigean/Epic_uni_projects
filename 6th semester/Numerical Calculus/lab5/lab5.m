A = [9,  1,  1;
     2, 10,  3;
     3,  4, 11];

b = [10; 19; 0];

x0 = [0; 0; 0];

err = 1e-5;
maxnit = 100;

disp('=== Jacobi Method ===');
[x_jacobi, nit_jacobi] = jacobi_method_lab5(A, b, x0, err, maxnit);
fprintf('Calculated Solution:\n');
disp(x_jacobi);
fprintf('Iterations required: %d\n\n', nit_jacobi);

disp('=== Gauss-Seidel Method ===');
[x_gs, nit_gs] = gauss_seidel_method_la5(A, b, x0, err, maxnit);
fprintf('Calculated Solution:\n');
disp(x_gs);
fprintf('Iterations required: %d\n', nit_gs);









disp('=== APPLICATION 1 ===')
n = 1000;
err = 1e-5;
maxnit = 5000;

main_diag = 5 * ones(n, 1);
sub_diag = -1 * ones(n-1, 1);
super_diag = -1 * ones(n-1, 1);

A = diag(main_diag) + diag(sub_diag, -1) + diag(super_diag, 1);


b = 3 * ones(n, 1);
b(1) = 4;
b(n) = 4;

x0 = zeros(n, 1);
disp('=== Application 1: Jacobi Method ===');
[x_jacobi, nit_jacobi] = jacobi_method_lab5(A, b, x0, err, maxnit);
fprintf('Jacobi method converged in %d iterations.\n', nit_jacobi);

disp('First 5 elements of the Jacobi solution:');
disp(x_jacobi(1:5));
disp('Last 5 elements of the Jacobi solution:');
disp(x_jacobi(end-4:end));
fprintf('\n');

disp('=== Application 1: Gauss-Seidel Method ===');
[x_gs, nit_gs] = gauss_seidel_method_la5(A, b, x0, err, maxnit);
fprintf('Gauss-Seidel method converged in %d iterations.\n', nit_gs);

disp('First 5 elements of the Gauss-Seidel solution:');
disp(x_gs(1:5));
disp('Last 5 elements of the Gauss-Seidel solution:');
disp(x_gs(end-4:end));





disp('=== APPLICATION 2 ===')

A = [10,  7,  8,  7;
      7,  5,  6,  5;
      8,  6, 10,  9;
      7,  5,  9, 10];

b = [32; 23; 33; 31];

x = A \ b;
disp('=== Part a: Original Solution x ===');
disp(x);
disp(' ');

b_tilde = [32.1; 22.9; 33.1; 30.9];
x_tilde_b = A \ b_tilde;

err_in_b = norm(b - b_tilde) / norm(b);
err_out_b = norm(x - x_tilde_b) / norm(x);

disp('=== Part b: Perturbed b ===');
disp('Solution x_tilde_b:');
disp(x_tilde_b);
fprintf('Input relative error in b: %e\n', err_in_b);
fprintf('Output relative error in x: %e\n\n', err_out_b);

disp('--- EXPLANATION: Part b ---');
disp('Notice how a tiny input relative error (roughly 0.33%) in the vector b');
disp('caused a massive output relative error (roughly 820%) in the solution x.');
disp('The exact solution of [1; 1; 1; 1] is completely lost.');
disp(' ');
A_tilde = [10.0, 7.00,  8.1,  7.2;
            7.8, 5.04,  6.0,  5.0;
            8.0, 5.98,  9.9,  9.0;
            6.99, 4.99, 9.0, 98.0];

x_tilde_A = A_tilde \ b;

err_in_A = norm(A - A_tilde) / norm(A);
err_out_A = norm(x - x_tilde_A) / norm(x);

disp('=== Part c: Perturbed A ===');
disp('Solution x_tilde_A:');
disp(x_tilde_A);
fprintf('Input relative error in A: %e\n', err_in_A);
fprintf('Output relative error in x: %e\n\n', err_out_A);

disp('--- EXPLANATION: Part c ---');
disp('Similarly, changing the matrix A also results in an entirely wrong solution.');
disp('This confirms the system is highly sensitive to perturbations in ANY of its input data.');
disp(' ');

disp('=== Part d: Explaining the Phenomenon ===');
cond_A = cond(A);
fprintf('Condition number of A: %e\n\n', cond_A);

disp('--- EXPLANATION: The Phenomenon ---');
disp('This catastrophic loss of accuracy is due to the matrix being "ill-conditioned."');
disp('The condition number cond(A) acts as a multiplier for how errors propagate.');
disp('As stated in the lecture notes: "But if cond(A) is large, then there may be');
disp('small relative perturbations of b that will lead to large relative perturbations in x."');
disp('Because Wilson''s matrix has a large condition number (nearly 3000), it magnifies');
disp('tiny input errors into massive output failures, demonstrating severe numerical instability.');
disp(' ');






disp('=== EXERCISE 3 ===')

ns = [10, 1000];
err = 1e-5;
maxnit = 5000;

for i = 1:length(ns)
    n = ns(i);
    fprintf('\n========================================\n');
    fprintf('Testing for n = %d\n', n);
    fprintf('========================================\n');

    main_diag = 5 * ones(n, 1);
    sub_diag = -1 * ones(n, 1);
    super_diag = -1 * ones(n, 1);

    A = spdiags([sub_diag, main_diag, super_diag], [-1, 0, 1], n, n);

    A(1, n) = -1;
    A(n, 1) = -1;

    b = 3 * ones(n, 1);

    x0 = zeros(n, 1);

    D = diag(diag(A));
    L = -tril(A, -1);
    U = -triu(A, 1);

    T_J = D \ (L + U);

    rho_T_J = max(abs(eig(full(T_J))));
    omega_opt = 2 / (1 + sqrt(1 - rho_T_J^2));

    fprintf('Optimal relaxation parameter (omega): %.4f\n\n', omega_opt);


    [~, nit_jacobi] = jacobi_method_lab5(A, b, x0, err, maxnit);
    fprintf('Jacobi iterations:       %d\n', nit_jacobi);

    [~, nit_gs] = gauss_seidel_method_la5(A, b, x0, err, maxnit);
    fprintf('Gauss-Seidel iterations: %d\n', nit_gs);

    [x_sor, nit_sor] = sor_method_lab5(A, b, omega_opt, x0, err, maxnit);
    fprintf('SOR iterations:          %d\n\n', nit_sor);

    disp('First 5 elements of the calculated solution:');
    disp(x_sor(1:5));
    disp('Last 5 elements of the calculated solution:');
    disp(x_sor(end-4:end));
end
