function [x, nit] = sor_method_lab5(A, b, omega, x0, err, maxnit)
    D = diag(diag(A));
    L = -tril(A, -1);
    U = -triu(A, 1);

    M = (D / omega) - L;
    N = ((1 - omega) / omega) * D + U;

    x = x0;

    for nit = 1:maxnit
        x_new = M \ (N * x + b);

        if norm(x_new - x, inf) <= err
            x = x_new;
            return;
        end

        x = x_new;
    end

    warning('SOR method reached the maximum number of iterations without converging.');
end
