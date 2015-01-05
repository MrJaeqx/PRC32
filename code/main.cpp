#include <iostream>

using namespace std;

#include "FileStructure.h"
#include "Key.h"

int main()
{
    FileStructure f;
    Key head;

    Key* keyCurrent;
    Key* keyNext;

    Value* valueCurrent;
    Value* valueNext;

    bool ready = false;
    
    // load file
    std::cout << "Loading file..." << std::endl;
    f.loadFile("data/gibberish.bin", head);

    // sorteer keys
    std::cout << "Sorting keys..." << std::endl;
    while(!ready)
    {
        ready = true;

        // keys nodig voor het sorteren
        keyCurrent = &head;
        keyNext = keyCurrent->getNext();

        //sorteer keys zolang er nog keys zijn
        while (keyNext != NULL)
        {
            //key verplaatsen
            if(keyCurrent->getKey() > keyNext->getKey())
            {
                ready = false;

                string keyTemp = keyNext->getKey();
                Value* keyTempValue = keyNext->getValue();

                keyNext->setKey(keyCurrent->getKey());
                keyNext->setValue(keyCurrent->getValue());

                keyCurrent->setKey(keyTemp);
                keyCurrent->setValue(keyTempValue);
            }

            // ga naar de volgende key
            keyCurrent = keyNext;
            keyNext = keyNext->getNext();
        }
    }

    // ga weer naar de eerste key
    keyCurrent = &head;
    keyNext = keyCurrent->getNext();

    // sorteer values
    std::cout << "Sorting values..." << std::endl;
    while(keyCurrent != NULL)
    {
        ready = false;

        while(!ready)
        {
            ready = true;

            // values voor het sorteren
            valueCurrent = keyCurrent->getValue();
            valueNext = valueCurrent->getNext();

            // sorteer zolang er values zijn
            while(valueNext != NULL)
            {
            	// value verplaatsen
                if(valueCurrent->getValue() > valueNext->getValue())
                {
                    ready = false;

                    string temp = valueNext->getValue();
                    valueNext->setValue(valueCurrent->getValue());
                    valueCurrent->setValue(temp);
                }

                // ga naar volgende value
                valueCurrent = valueNext;
                valueNext = valueNext->getNext();
            }
        }

        // ga naar volgende key zolang ze er zijn
        keyCurrent = keyNext;
        if(keyNext != NULL)
        {
            keyNext = keyNext->getNext();
        }  
    }

    //head.print();

    // save sorted data into a new file called sorted.bin
    std::cout << "Saving file..." << std::endl;
    f.saveFile(head, "sorted.bin");

    std::cout << "Done!" << std::endl;
    
    return 0;
}
