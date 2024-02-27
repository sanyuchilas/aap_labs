void qSort(int *a, int first, int last) {
    if (first < last) {
        int left = first, right = last, middle = a[(left + right) / 2];
    do {
        while (a[left] < middle) left++;
        while (a[right] > middle) right--;
        if (left <= right) {
            int tmp = a[left];
            a[left] = a[right];
            a[right] = tmp;
            left++;
            right--;
        }

    } while (left <= right);
    qSort(a, first, right);
    qSort(a, left, last);
    }
}

void quickSort(int *a, int n)   {
    qSort(a, 0, n-1);
}