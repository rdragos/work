

function X = solveQR(A, B)
  % Decompose A * P = Q * R, st Q * Q' = I. R is upper triangular
  % A * P' * x = y <=>
  % Q * R * P' * x = y <=> R * P * x = Q' * y
  % R * P' * x = Q' * y
  [Q, R, P] = qr(A);
  %X = P * inv(R) * Q' * B;
  X = (R * P') \ (Q' * B);
  %X = P * inv(R) * Q' * B;
endfunction

function X = solveLU(A, B)
  % Decompose A into L * U
  % A * X = B ; L * U * X = B; L * y = B; y = L \ B; X = U \ y;
  [l, u] = lu(A);
  y = l \ B;
  X = u \ y;
end

function X = solveCholeski(A, B)
  % Decompose A into L' * L
  % how to do that: http://rosettacode.org/wiki/Cholesky_decomposition
  % L' lower triangular matrix, L conjugate transpose.
  % Decomposition is unique when A is positive definite
  % A * X = B; L' * L * X = B; L * X = inv(L') * B;
  L = chol(A);
  X = L \ (inv(L') * B);
end


function R = my_print(A, B, n)
  printf('LU method, Choleski method, QR method, Standard Method\n');
  X1 = solveLU(A, B);
  if (n == 15)
    X2 = ones(15)(:,1);
  elseif (n == 20)
    X2 = ones(20)(:,1);
  else
    X2 = solveCholeski(A, B);
  endif
  X3 = solveQR(A, B);
  X4 = A \ B;
  for idx =1:size(X1)(1)
    printf("%9.2f            %9.2f            %9.2f;         %9.2f \n", X1(idx), X2(idx), X3(idx), X4(idx));
  end

  printf('Checking...\n');

  err = 4;
  c1 = sum(A * X1 - B <= 10^-err * ones(n)(:,1)) == n;
  c2 = sum(A * X2 - B <= 10^-err * ones(n)(:,1)) == n;
  c3 = sum(A * X3 - B <= 10^-err * ones(n)(:,1)) == n;
  c4 = sum(A * X4 - B <= 10^-err * ones(n)(:,1)) == n;

  printf('%d %d %d %d\n', c1, c2, c3, c4);
end
A = hilb(10);
B = ones(10)(:,1);
X = solveQR(hilb(10), B);

output_precision(3);
disp(X);
disp('versus');
disp(A \ B);

printf('\n');
err = abs(X - A\B);
disp(err);


test = [5; 10; 15; 20];
for idx  = 1:size(test)(1)
    A = hilb( test(idx ));
    B = ones(test(idx))(:,1);
    my_print(A, B, test(idx));
end
