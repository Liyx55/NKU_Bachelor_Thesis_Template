//
// Created by 佘崧林 on 2020/1/22.
//

template<typename DataType>
AbstractTree<DataType>::~AbstractTree() {
    if (this->leftChild != nullptr) {
        delete this->leftChild;
        this->leftChild = nullptr;
    }
    if (this->rightChild != nullptr) {
        delete this->rightChild;
        this->rightChild = nullptr;
    }
}

template<typename DataType>
AbstractTree<DataType>::AbstractTree(const AbstractTree &copy) {
    this->nodeData = copy.getNodeData();
    if (copy.getLeftChild() != nullptr) {
        this->leftChild = new AbstractTree(*copy.getLeftChild());
        this->leftChild->setParent(this);
    }
    if (copy.getRightChild() != nullptr) {
        this->rightChild = new AbstractTree(*copy.getRightChild());
        this->rightChild->setParent(this);
    }
}

template<typename DataType>
AbstractTree<DataType>::AbstractTree(const DataType &data, AbstractTree *lt, AbstractTree *rt)
    : nodeData(data), leftChild(lt), rightChild(rt) {
    assert(lt->parentTree == nullptr && rt->parentTree == nullptr);
    lt->parentTree = this;
    rt->parentTree = this;
}

template<typename DataType>
void AbstractTree<DataType>::preOrderForEach(const std::function<void(AbstractTree<mpz_class> *)> &exec) {
    exec(this);
    if (this->leftChild != nullptr) this->leftChild->preOrderForEach(exec);
    if (this->rightChild != nullptr) this->rightChild->preOrderForEach(exec);
}

template<typename DataType>
std::list<DataType> AbstractTree<DataType>::preOrderGetLeafList(){
    std::list<DataType> leafList;
    this->preOrderForEach([&leafList](AbstractTree *root) {
        if (root->leftChild == nullptr && root->rightChild == nullptr) leafList.push_back(root->getNodeData());
    });
    return leafList;
}

