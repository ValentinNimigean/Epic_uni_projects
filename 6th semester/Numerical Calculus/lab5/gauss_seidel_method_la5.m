function [x, nit] = gauss_seidel_method_la5(A, b, x0, err, maxnit)
    D = diag(diag(A));
    L = -tril(A, -1);
    U = -triu(A, 1);

    M = D - L;

    x = x0;

    for nit = 1:maxnit
        x_new = M \ (U * x + b);

        if norm(x_new - x, inf) <= err
            x = x_new;
            return;
        end

        x = x_new;
    end

    warning('Gauss-Seidel method reached the maximum number of iterations without converging.');
end
