void shakerSort(int a[], long size)
{
  long j, k = size-1;
  long lb=1, ub = size-1; // bounds of unsorted part of the array
  int x;

  do
  {
    // from bottom to top passage 
    for( j=ub; j>0; j-- )
    {
      if ( a[j-1] > a[j] )
      {
        x=a[j-1]; a[j-1]=a[j]; a[j]=x;
        k=j;
      }
    }

    lb = k+1;

    // passage from top to bottom 
    for (j=1; j<=ub; j++)
    {
      if ( a[j-1] > a[j] )
      {
        x=a[j-1]; a[j-1]=a[j]; a[j]=x;
        k=j;
      }
    }

    ub = k-1;
  }
  while ( lb < ub );
}