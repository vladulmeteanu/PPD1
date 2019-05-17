/input example: 1 2 3 4 5
//to the left
int temp = a[0]; //remember first element
for(i=0;i<n-1;i++)
{
    a[i] = a[i+1]; //move all element to the left except first one
}
a[n-1] = temp; //assign remembered value to last element
//output: 2 3 4 5 1
cout << "To left: " << endl;
for(i=0;i<n;i++)
    cout << a[i] << endl;

//to the right
temp = a[n-1]; //remember last element
for(i=n-1;i>=0;i--)
{
    a[i+1] = a[i]; //move all element to the right except last one
}
a[0] = temp; //assign remembered value to first element
//output: 1 2 3 4 5 because elements are shifted back by right shift
cout << "To right: " << endl;
for(i=0;i<n;i++)
    cout << a[i] << endl;