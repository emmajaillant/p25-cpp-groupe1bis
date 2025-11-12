#include <iostream>
#include <stdexcept>

// Nous allons implémenter une pile d'entiers de manière très basique.
// Nous la complexifierons par la suite.

// La pile est constituée:
//    - d'un tableau d'entier, avec sa taille et son nombre d'éléments empilés
//    - des quatre fonctions: push, pop, top, print, is_empty et is_full
//      (qui testent si la pile est resp. vide ou pleine)
//      il faut les utiliser dans votre code de push et pop

void print(int *stack, int size)
// cette fonction affiche les entiers empilés
{
    std::cout << "[ ";
    int i = 0;
    while (i < size)
    {
        std::cout << stack[i] << std::endl;
        i = i + 1;
    }
    std::cout << "[" << std::endl;
    
}

// renvoie true si la pile est vide, false sinon
bool is_empty(int size, int nb)
{
    if (nb == 0)
    {
        return true;
    }
    else
    {
        return false ;
    }
}

// renvoie true si la pile est pleine, false sinon
bool is_full(int size, int nb)
{
    if (nb == size)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void push(int *stack, int size, int nb, int a)
// cette fonction ajoute un entier à la pile passé en argument
// elle doit s'assurer que la pile n'est pas pleine avant d'empiler
// elle lance une exception si problème
{
    
    if (is_full(size, nb)){
        throw std::invalid_argument(std::string("we throw an exception of type: invalid_argument ") + std::to_string(i));
    }
    int stack[nb] = a;
    nb = nb + 1;

}

int top(int stack, int size, int nb) // (cette fonction ne dépile pas)
// cette fonction retourne l'entier en haut de la pile (le dernier empilé)
// à la sortie de cette fonction l'élément retourné reste dans la pile
// elle doit s'assurer que la pile n'est pas vide avant de la dépiler
// elle lance une exception si problème
{
    if (is_empty(size, nb)){
        throw std::invalid_argument(std::string("we throw an exception of type: invalid_argument ") + std::to_string(i));
    }
    std::cout << stack[nb] << std::endl;
}

int pop(int stack, int size, int nb) // (cette fonction dépile)
// cette fonction retourne l'entier en haut de la pile (le dernier empilé)
// à la sortie de cette fonction l'élément retourné n'est plus compté dans la pile
// elle doit s'assurer que la pile n'est pas vide avant de la dépiler
// elle lance une exception si problème
{
    if (is_empty(size, nb)){
        throw std::invalid_argument(std::string("we throw an exception of type: invalid_argument ") + std::to_string(i));
    }
    int e = top(stack, size, nb);
    nb = nb - 1;
    return e; 
}

#include <stdexcept>
// https://en.cppreference.com/w/cpp/header/stdexcept.html
// pour un exemple d'exception voir le fichier exception.cpp

int main()
{

    // on définit les 3 variables constituant la pile
    int size = 5;
    int stack[size];
    int nb = 0;

    // rajoutez aux blocks catch les erreurs
    // pouvant être déclenchées par les opérations sur la pile
    try
    {
        print(stack, size, nb); // affiche [ [
        push(stack, size, nb, -17);

        // on affiche l'élément en haut de pile
        std::cout << top(stack, size, nb) << std::endl; // affiche -17

        print(stack, size, nb); // affiche [-17 90 [

        int e = pop(stack, size, nb);
        std::cout << e << std::endl;
        print(stack, size, nb); // affiche [-17 [

        push(stack, size, nb, 20);
        push(stack, size, nb, -78);
        push(stack, size, nb, -9);
        push(stack, size, nb, -56);
        push(stack, size, nb, -9);
        push(stack, size, nb, 68);
    }
    catch (std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (std::overflow_error &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Une erreur inattendue est survenue." << std::endl;
    }
}