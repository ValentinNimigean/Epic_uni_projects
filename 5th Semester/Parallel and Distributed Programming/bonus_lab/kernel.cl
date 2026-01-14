__kernel void multiply_poly(__global const int* A, int n, 
                            __global const int* B, int m, 
                            __global int* C) {
    // Get the index of the result coefficient (k)
    int k = get_global_id(0);
    int res_size = n + m - 1;

    if (k < res_size) {
        int sum = 0;
        // Each thread calculates C[k] = sum of A[i]*B[j] where i+j=k
        for (int i = 0; i <= k; i++) {
            int j = k - i;
            if (i < n && j < m) {
                sum += A[i] * B[j];
            }
        }
        C[k] = sum;
    }
}