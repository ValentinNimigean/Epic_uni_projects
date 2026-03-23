function [x, nit] = jacobi_method_lab5(A, b, x0, err, maxnit)
    D = diag(diag(A));

    L = -tril(A, -1);
    U = -triu(A, 1);

    x = x0;

    for nit = 1:maxnit

        x_new = D \ ((L + U) * x + b);

        if norm(x_new - x, inf) <= err
            x = x_new;
            return;
        end

        x = x_new;
    end

    warning('Jacobi method reached the maximum number of iterations without converging.');
end
