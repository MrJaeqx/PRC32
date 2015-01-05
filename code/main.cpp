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

    // sort all data
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

            keyCurrent = keyNext;
            keyNext = keyNext->getNext();
        }
    }

    std::cout << "Sorting values..." << std::endl;
    keyCurrent = &head;
    keyNext = keyCurrent->getNext();

    //sort values
    while(keyCurrent != NULL)
    {
        ready = false;

        while(!ready)
        {
            ready = true;
            valueCurrent = keyCurrent->getValue();
            valueNext = valueCurrent->getNext();

            while(valueNext != NULL)
            {
                if(valueCurrent->getValue() > valueNext->getValue())
                {
                    ready = false;

                    string temp = valueNext->getValue();
                    valueNext->setValue(valueCurrent->getValue());
                    valueCurrent->setValue(temp);
                }

                valueCurrent = valueNext;
                valueNext = valueNext->getNext();
            }
        }

        keyCurrent = keyNext;
        if(keyNext != NULL)
        {
            keyNext = keyNext->getNext();
        }  
    }

    head.print();

    // save sorted data into a new file called sorted.bin
    std::cout << "Saving file..." << std::endl;
    f.saveFile(head, "sorted.bin");

    std::cout << "Done!" << std::endl;
    
    return 0;
}
