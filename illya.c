int Fibbonaci(int num)
{
    if (num == 0 || num == 1)
    {
        return 1;
    }
    return Fibbonaci(num-1) + Fibbonaci(num -2);
}