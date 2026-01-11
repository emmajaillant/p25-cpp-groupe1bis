#include <iostream>
#include <stdexcept>

class Stack
{
private:
    int size;   
    int nb;    
    int* tab;   

public:
    Stack(int size)
        : size(size), nb(0)
    {
        std::cout << "Stack::Stack(int)\n";
        tab = new int[size];
    }

Stack(const Stack& other)
    : size(other.size), nb(other.nb)
{
    tab = new int[size];
    for (int i = 0; i < nb; i++)
        tab[i] = other.tab[i];
}


Stack(int size)
{
    tab = new int[size];
}

~Stack()
{
    delete[] tab;
}


void print()
{
    std::cout << "[ ";
    for (int i = 0; i < nb; i++)
    {
        std::cout << tab[i] << " ";
    }
    std::cout << "]" << std::endl;
}

bool is_empty()
{
    return nb == 0;
}

bool is_full()
{
    return nb == size;
}

void push(int x)
{
    if (is_full())
    {
        throw std::invalid_argument("stack full");
    }
    tab[nb] = x;
    nb = nb + 1;
}

int top()
{
    if (is_empty())
    {
        throw std::invalid_argument("stack empty");
    }
    return tab[nb - 1];
}

int pop()
{
    if (is_empty())
    {
        throw std::invalid_argument("stack empty");
    }
    nb = nb - 1;
    return tab[nb];
}
};


int main()
{
    try
    {
        Stack s1(5);
        s1.push(10);
        s1.push(20);
        s1.print();

        Stack s2(s1);   // constructeur de copie
        s2.push(30);
        s2.print();

        Stack s3(3);
        s3 = s1;        // opérateur d'affectation
        s3.print();
    }
    catch (std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (std::overflow_error &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Une erreur inattendue est survenue." << std::endl;
    }

    return 0;
}