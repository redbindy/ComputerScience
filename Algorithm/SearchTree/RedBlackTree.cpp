#include "RedBlackTree.h"

enum EConstant
{
    SENTINEL_NONE = INT32_MIN,
    PRINT_WIDTH = 129,
    PRINT_DEPTH = 7
};

RedBlackTree::RedBlackTree()
    : mpRoot(nullptr)
    , mpNil(nullptr)
{
    mpNil = new RedBlackNode(EConstant::SENTINEL_NONE);
    mpNil->IsBlack = true;

    mpRoot = mpNil;
}

RedBlackTree::~RedBlackTree()
{
    mpRoot = destroyRecursive(mpRoot);

    delete mpNil;
}

RedBlackTree::RedBlackNode* RedBlackTree::destroyRecursive(RedBlackNode* const pNode)
{
    if (pNode != mpNil)
    {
        pNode->pLeft = destroyRecursive(pNode->pLeft);
        pNode->pRight = destroyRecursive(pNode->pRight);

        delete pNode;
    }

    return nullptr;
}

bool RedBlackTree::HasKey(const int key) const
{
    const RedBlackNode* const pNode = searchRecursive(mpRoot, key);

    return pNode != mpNil;
}

void RedBlackTree::InsertKey(const int key)
{
    mpRoot = insertKeyRecursive(mpRoot, key);

    // case 1
    if (!mpRoot->IsBlack)
    {
        mpRoot->SwapColor();
    }
}

void RedBlackTree::RemoveKey(const int key)
{
    bool isFinished = false;
    mpRoot = removeKeyRecursive(mpRoot, key, isFinished);
}

void RedBlackTree::PrintTree() const
{
    assert(mpRoot != mpNil);

    system("cls");

    constexpr int BUFFER_SIZE = EConstant::PRINT_WIDTH * EConstant::PRINT_DEPTH;

    std::vector<RedBlackNode*> screenData(BUFFER_SIZE, nullptr);

    writeTreeDataRecursive(mpRoot, 0, PRINT_WIDTH / 2, 64, screenData);

    for (int y = 0; y < PRINT_DEPTH; ++y)
    {
        for (int x = 0; x < PRINT_WIDTH; ++x)
        {
            const int i = y * PRINT_WIDTH + x;

            if (screenData[i] == nullptr)
            {
                std::cout << ' ';
            }
            else
            {
                if (screenData[i]->IsBlack)
                {
                    std::cout << "\033[37m";
                }
                else
                {
                    std::cout << "\033[31m";
                }

                std::cout << screenData[i]->Key;
            }
        }
        std::cout << std::endl;
    }
}

const RedBlackTree::RedBlackNode* RedBlackTree::searchRecursive(const RedBlackNode* const pNode, const int key) const
{
    if (pNode == mpNil)
    {
        return mpNil;
    }

    if (pNode->Key == key)
    {
        return pNode;
    }

    if (key < pNode->Key)
    {
        return searchRecursive(pNode->pLeft, key);
    }

    return searchRecursive(pNode->pRight, key);
}

RedBlackTree::RedBlackNode* RedBlackTree::insertKeyRecursive(RedBlackNode* const pNode, const int key)
{
    if (pNode == mpNil)
    {
        return new RedBlackNode(key, mpNil);
    }

    RedBlackNode* pGrandParent = pNode;
    if (key < pNode->Key)
    {
        if (pNode->pLeft == mpNil)
        {
            pNode->pLeft = new RedBlackNode(key, mpNil);

            return pNode;
        }

        pGrandParent->pLeft = insertKeyRecursive(pNode->pLeft, key);

        RedBlackNode* pParent = pGrandParent->pLeft;
        if (!pParent->IsBlack)
        {
            if (pParent->pLeft->IsBlack && pParent->pRight->IsBlack)
            {
                return pGrandParent;
            }

            RedBlackNode* const pUncle = pGrandParent->pRight;
            if (!pUncle->IsBlack)
            {
                // case 3
                pGrandParent->SwapColor();
                pParent->SwapColor();
                pUncle->SwapColor();
            }
            else
            {
                // case 4
                if (key >= pParent->Key)
                {
                    pParent = rotateLeft(pParent);
                    pGrandParent->pLeft = pParent;
                }

                pGrandParent->SwapColor();
                pParent->SwapColor();

                pGrandParent = rotateRight(pGrandParent);
            }
        }

        // case 2
        // if (pParent->IsBlack) { do nothing };
    }
    else
    {
        if (pNode->pRight == mpNil)
        {
            pNode->pRight = new RedBlackNode(key, mpNil);

            return pNode;
        }

        pGrandParent->pRight = insertKeyRecursive(pNode->pRight, key);

        RedBlackNode* pParent = pGrandParent->pRight;
        if (!pParent->IsBlack)
        {
            if (pParent->pLeft->IsBlack && pParent->pRight->IsBlack)
            {
                return pGrandParent;
            }

            RedBlackNode* const pUncle = pGrandParent->pLeft;
            if (!pUncle->IsBlack)
            {
                // case 3
                pGrandParent->SwapColor();
                pParent->SwapColor();
                pUncle->SwapColor();
            }
            else
            {
                // case 4
                if (key < pParent->Key)
                {
                    pParent = rotateRight(pParent);
                    pGrandParent->pRight = pParent;
                }

                pGrandParent->SwapColor();
                pParent->SwapColor();

                pGrandParent = rotateLeft(pGrandParent);
            }
        }

        // case 2
        // if (pParent->IsBlack) { do nothing };
    }

    return pGrandParent;
}

RedBlackTree::RedBlackNode* RedBlackTree::removeKeyRecursive(RedBlackNode* const pNode, const int key, bool& outIsFinished)
{
    if (pNode == mpNil)
    {
        return mpNil;
    }

    if (pNode->Key == key)
    {
        RedBlackNode* const pLeft = pNode->pLeft;
        RedBlackNode* const pRight = pNode->pRight;

        if (pLeft != mpNil && pRight != mpNil)
        {
            RedBlackNode* pPredecessor = pLeft;
            while (pPredecessor->pRight != mpNil)
            {
                pPredecessor = pPredecessor->pRight;
            }

            const int predecessorKey = pPredecessor->Key;

            pNode->pLeft = removeKeyRecursive(pLeft, predecessorKey, outIsFinished);

            pNode->Key = predecessorKey;

            return pNode;
        }

        const bool bParentBlack = pNode->IsBlack;

        delete pNode;

        RedBlackNode* pRetNode = nullptr;
        if (pLeft == mpNil)
        {
            pRetNode = pRight;
        }
        else
        {
            pRetNode = pLeft;
        }

        outIsFinished = !bParentBlack || !pRetNode->IsBlack;

        if (pRetNode != mpNil && bParentBlack && !pRetNode->IsBlack)
        {
            pRetNode->SwapColor();
        }

        return pRetNode;
    }

    RedBlackNode* pRetNode = pNode;

    if (key < pNode->Key)
    {
        pNode->pLeft = removeKeyRecursive(pNode->pLeft, key, outIsFinished);
    }
    else
    {
        pNode->pRight = removeKeyRecursive(pNode->pRight, key, outIsFinished);
    }

    if (!outIsFinished)
    {
        pRetNode = executeRemoveStrategyRecursive(pNode, key, outIsFinished);
    }

    return pRetNode;
}

RedBlackTree::RedBlackNode* RedBlackTree::executeRemoveStrategyRecursive(RedBlackNode* const pNode, const int key, bool& outIsFinished)
{
    RedBlackNode* pRetNode = pNode;
    RedBlackNode* pSibling = nullptr;
    if (key < pNode->Key)
    {
        pSibling = pNode->pRight;

        // case 2
        if (!pSibling->IsBlack)
        {
            pRetNode->SwapColor();
            pSibling->SwapColor();

            pRetNode = rotateLeft(pNode);
            pRetNode->pLeft = executeRemoveStrategyRecursive(pNode, key, outIsFinished);
        }
        else
        {
            if (pNode->IsBlack)
            {
                // case 3
                if (pSibling->IsBlack && pSibling->pLeft->IsBlack && pSibling->pRight->IsBlack)
                {
                    pSibling->SwapColor();
                }
            }
            else
            {
                // case 4
                if (pSibling->pLeft->IsBlack && pSibling->pRight->IsBlack)
                {
                    pNode->SwapColor();
                    pSibling->SwapColor();

                    outIsFinished = true;
                }
                else
                {
                    // case 5
                    if (pSibling->pRight->IsBlack)
                    {
                        pSibling->SwapColor();

                        pSibling = rotateRight(pSibling);
                        pSibling->SwapColor();

                        pNode->pRight = pSibling;
                    }

                    // case 6
                    pNode->SwapColor();
                    pSibling->SwapColor();
                    pSibling->pRight->SwapColor();

                    pRetNode = rotateLeft(pNode);

                    outIsFinished = true;
                }
            }
        }
    }
    else
    {
        pSibling = pNode->pLeft;

        // case 2
        if (!pSibling->IsBlack)
        {
            pRetNode->SwapColor();
            pSibling->SwapColor();

            pRetNode = rotateRight(pNode);
            pRetNode->pRight = executeRemoveStrategyRecursive(pNode, key, outIsFinished);
        }
        else
        {
            if (pNode->IsBlack)
            {
                // case 3
                if (pSibling->IsBlack && pSibling->pLeft->IsBlack && pSibling->pRight->IsBlack)
                {
                    pSibling->SwapColor();
                }
            }
            else
            {
                // case 4
                if (pSibling->pLeft->IsBlack && pSibling->pRight->IsBlack)
                {
                    pNode->SwapColor();
                    pSibling->SwapColor();

                    outIsFinished = true;
                }
                else
                {
                    // case 5
                    if (pSibling->pLeft->IsBlack)
                    {
                        pSibling->SwapColor();

                        pSibling = rotateRight(pSibling);
                        pSibling->SwapColor();

                        pNode->pLeft = pSibling;
                    }

                    // case 6
                    pNode->SwapColor();
                    pSibling->SwapColor();
                    pSibling->pLeft->SwapColor();

                    pRetNode = rotateRight(pNode);

                    outIsFinished = true;
                }
            }
        }
    }

    return pRetNode;
}

RedBlackTree::RedBlackNode* RedBlackTree::rotateLeft(RedBlackNode* const pNode)
{
    assert(pNode != mpNil);
    assert(pNode->pRight != mpNil);

    RedBlackNode* const pRight = pNode->pRight;
    RedBlackNode* const pRightLeft = pRight->pLeft;

    pRight->pLeft = pNode;
    pNode->pRight = pRightLeft;

    return pRight;
}

RedBlackTree::RedBlackNode* RedBlackTree::rotateRight(RedBlackNode* const pNode)
{
    assert(pNode != mpNil);
    assert(pNode->pLeft != mpNil);

    RedBlackNode* const pLeft = pNode->pLeft;
    RedBlackNode* const pLeftRight = pLeft->pRight;

    pLeft->pRight = pNode;
    pNode->pLeft = pLeftRight;

    return pLeft;
}

void RedBlackTree::writeTreeDataRecursive(RedBlackNode* const pNode, const int depth, const int index, const int gap, std::vector<RedBlackNode*>& outScreenData) const
{
    assert(pNode != nullptr);
    assert(depth >= 0);

    if (pNode == mpNil)
    {
        return;
    }

    outScreenData[EConstant::PRINT_WIDTH * depth + index] = pNode;

    const int nextGap = gap / 2;

    writeTreeDataRecursive(pNode->pLeft, depth + 1, index - nextGap, nextGap, outScreenData);
    writeTreeDataRecursive(pNode->pRight, depth + 1, index + nextGap, nextGap, outScreenData);
}
