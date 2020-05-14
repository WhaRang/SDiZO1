/**
 * Created by Aliaksei Tokarau on 4/1/2020.
 * plik: rb_tree.cpp
 * zawartosc: implementacja metod zadeklarowanych w rb_tree.h
 */


#include "rb_tree.h"


rb_tree::rb_tree() {
    this->root = nullptr;
}


void rb_tree::left_rotation(rb_tree::Node *node) {
    Node *new_node = node->right;
    Node *parent = get_parent(node);
    assert(new_node != nullptr);


    node->right = new_node->left;
    new_node->left = node;
    node->parent = new_node;

    if (node->right != nullptr) {
        node->right->parent = node;
    }

    if (parent != nullptr) {
        if (node == parent->left) {
            parent->left = new_node;
        } else if (node == parent->right) {
            parent->right = new_node;
        }
    } else {
        this->root = new_node;
    }
    new_node->parent = parent;
}


void rb_tree::right_rotation(rb_tree::Node *node) {
    Node *new_node = node->left;
    Node *parent = get_parent(node);
    assert(new_node != nullptr);

    node->left = new_node->right;
    new_node->right = node;
    node->parent = new_node;

    if (node->left != nullptr) {
        node->left->parent = node;
    }

    if (parent != nullptr) {
        if (node == parent->left) {
            parent->left = new_node;
        } else if (node == parent->right) {
            parent->right = new_node;
        }
    } else {
        this->root = new_node;
    }
    new_node->parent = parent;
}


rb_tree::Node *rb_tree::get_parent(rb_tree::Node *node) {
    { return node == nullptr ? nullptr : node->parent; }
}


rb_tree::Node *rb_tree::get_grand_parent(rb_tree::Node *node) {
    return get_parent(get_parent(node));
}


rb_tree::Node *rb_tree::get_sibling(rb_tree::Node *node) {
    Node *parent = get_parent(node);

    if (parent == nullptr) {
        return nullptr;
    }

    if (node == parent->left) {
        return parent->right;
    } else {
        return parent->left;
    }
}


rb_tree::Node *rb_tree::get_uncle(rb_tree::Node *node) {
    Node *parent = get_parent(node);
    return get_sibling(parent);
}


void rb_tree::insert(int data) {
    Node *node = new Node(data);
    insert_Recurse(root, node);
    fix_violation(node);

    this->root = node;
    while (get_parent(this->root) != nullptr) {
        this->root = get_parent(this->root);
    }
}


void rb_tree::insert_Recurse(rb_tree::Node *root, rb_tree::Node *node) {
    if (root != nullptr) {
        if (node->data < root->data) {
            if (root->left != nullptr) {
                insert_Recurse(root->left, node);
                return;
            } else {
                root->left = node;
            }
        } else {
            if (root->right != nullptr) {
                insert_Recurse(root->right, node);
                return;
            } else {
                root->right = node;
            }
        }
    }

    node->parent = root;
    node->left = nullptr;
    node->right = nullptr;
    node->color = RED;
}


void rb_tree::fix_violation(rb_tree::Node *node) {
    if (get_parent(node) == nullptr) {
        node->color = BLACK;
    } else if (get_parent(node)->color == BLACK) {
        return;
    } else if (get_uncle(node) != nullptr && get_uncle(node)->color == RED) {
        get_parent(node)->color = BLACK;
        get_uncle(node)->color = BLACK;
        get_grand_parent(node)->color = RED;
        fix_violation(get_grand_parent(node));
    } else {
        Node *parent = get_parent(node);
        Node *grand_parent = get_grand_parent(node);

        if (node == parent->right && parent == grand_parent->left) {
            left_rotation(parent);
            node = node->left;
        } else if (node == parent->left && parent == grand_parent->right) {
            right_rotation(parent);
            node = node->right;
        }

        parent = get_parent(node);
        grand_parent = get_grand_parent(node);

        if (node == parent->left) {
            right_rotation(grand_parent);
        } else {
            left_rotation(grand_parent);
        }
        parent->color = BLACK;
        grand_parent->color = RED;
    }
}


rb_tree::Node *rb_tree::find(int key) {
    Node *curr_node = this->root;
    return this->find_Recurse(key, curr_node);
}


rb_tree::Node *rb_tree::find_Recurse(int key, rb_tree::Node *node) {
    if (!node) {
        return nullptr;
    }

    if (node->data == key) {
        return node;
    } else if (node->data > key) {
        return find_Recurse(key, node->left);
    } else if (node->data < key) {
        return find_Recurse(key, node->right);
    }
}


void rb_tree::replace(rb_tree::Node *node, rb_tree::Node *child) {
    child->parent = node->parent;
    if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }
}


bool rb_tree::remove_key(int key) {
    Node *node = this->find(key);

    if (node) {
        remove_node(node);
        return true;
    } else {
        return false;
    }
}


void rb_tree::remove_node(rb_tree::Node *node) {
    Node *replace_node;

    if (node->left && node->right) {
        node->data = successor(node)->data;
        remove_node(successor(node));
        return;
    }

    if (node->right || node->left) {
        replace_node = (node->right == nullptr) ? node->left : node->right;
    } else {
        replace_node = node;
    }

    replace(node, replace_node);
    if (node->color == BLACK) {
        if (replace_node && replace_node->color == RED) {
            replace_node->color = BLACK;
        } else {
            remove_case1(replace_node);
        }
    }

    if (node == replace_node) {
        if (node == node->parent->right) {
            node->parent->right = nullptr;
        } else {
            node->parent->left = nullptr;
        }
    }

    free(node);
}


void rb_tree::remove_case1(rb_tree::Node *node) {
    if (node->parent != nullptr) {
        remove_case2(node);
    }
}


void rb_tree::remove_case2(rb_tree::Node *node) {
    Node *sibling = get_sibling(node);

    if (sibling->color == RED) {
        node->parent->color = RED;
        sibling->color = BLACK;
        if (node == node->parent->left) {
            left_rotation(node->parent);
        } else {
            right_rotation(node->parent);
        }
    }


    remove_case3(node);
}


void rb_tree::remove_case3(rb_tree::Node *node) {
    Node *sibling = get_sibling(node);

    bool black_sibling_right = (!sibling->right) || (sibling->right->color == BLACK);
    bool black_sibling_left = (!sibling->left) || (sibling->left->color == BLACK);


    if ((node->parent->color == BLACK) && (sibling->color == BLACK) &&
        (black_sibling_left) && (black_sibling_right)) {
        sibling->color = RED;
        remove_case1(node->parent);
    } else {
        remove_case4(node);
    }
}


void rb_tree::remove_case4(rb_tree::Node *node) {
    Node *sibling = get_sibling(node);

    bool black_sibling_right = (!sibling->right) || (sibling->right->color == BLACK);
    bool black_sibling_left = (!sibling->left) || (sibling->left->color == BLACK);

    if ((node->parent->color == RED) && (sibling->color == BLACK) &&
        ((black_sibling_left) && (black_sibling_right))) {
        sibling->color = RED;
        node->parent->color = BLACK;
    } else {
        remove_case5(node);
    }
}


void rb_tree::remove_case5(rb_tree::Node *node) {
    Node *sibling = get_sibling(node);

    bool black_sibling_right = (!sibling->right) || (sibling->right->color == BLACK);
    bool black_sibling_left = (!sibling->left) || (sibling->left->color == BLACK);

    if (sibling->color == BLACK) {
        if ((node == node->parent->left) && (black_sibling_right) &&
            !black_sibling_left) {
            sibling->color = RED;
            sibling->left->color = BLACK;
            right_rotation(sibling);
        } else if ((node == node->parent->right) && (black_sibling_left) &&
                   !black_sibling_right) {
            sibling->color = RED;
            sibling->right->color = BLACK;
            left_rotation(sibling);
        }
    }

    remove_case6(node);
}


void rb_tree::remove_case6(rb_tree::Node *node) {
    Node *sibling = get_sibling(node);

    sibling->color = node->parent->color;
    node->parent->color = BLACK;

    if (node == node->parent->left) {
        if (sibling) {
            sibling->right->color = BLACK;
        }
        left_rotation(node->parent);
    } else {
        if (sibling) {
            sibling->left->color = BLACK;
        }
        right_rotation(node->parent);
    }

}


rb_tree::Node *rb_tree::successor(Node *node) {
    if (!node->right) {
        return nullptr;
    }

    Node *right_node = node->right;
    while (right_node->left) {
        right_node = right_node->left;
    }

    return right_node;
}


void rb_tree::print() {
    std::cout << "Data Structure: RED-BLACK TREE" << std::endl;
    this->print("", "", nullptr, true);
}


void rb_tree::print(std::string sp, std::string sn, Node *node, bool launch) {
    std::string cr, cl, cp;
    cr = cl = cp = "  ";
    cr[0] = 218;
    cr[1] = 196;
    cl[0] = 192;
    cl[1] = 196;
    cp[0] = 179;

    if (launch) {
        node = this->root;
    }

    std::string s, color;
    if (node) {
        s = sp;
        if (sn == cr) s[s.length() - 2] = ' ';
        print(s + cp, cr, node->right, false);

        s = s.substr(0, sp.length() - 2);
        color = node->color == RED ? "R" : "B";
        std::cout << s << sn << node->data << "(" << color << ")" << std::endl;

        s = sp;
        if (sn == cl) s[s.length() - 2] = ' ';
        print(s + cp, cl, node->left, false);
    }
}


void rb_tree::clear() {
    this->clear_Recurse(this->root);
    this->root = nullptr;
}


void rb_tree::clear_Recurse(rb_tree::Node *node) {
    if (node) {
        if (node->right) {
            clear_Recurse(node->right);
        }
        if (node->left) {
            clear_Recurse(node->left);
        }
        if (node->parent) {
            if (node == node->parent->right) {
                node->parent->right = nullptr;
            } else {
                node->parent->left = nullptr;
            }
        }
        free(node);
    }
}


void rb_tree::generate(int init_size) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(INT16_MIN, INT16_MAX);

    this->clear();
    for (int i = 0; i < init_size; i++) {
        this->insert(dist(mt));
    }
}


bool rb_tree::load_from_file(std::string file_name) {
    std::fstream file(file_name);

    if (!file) {
        return false;
    }

    int init_size;
    file >> init_size;

    this->clear();
    for (int i = 0; i < init_size; i++) {
        int element;
        file >> element;
        this->insert(element);
    }

    file.close();
    return true;
}