/*
 * 二叉树的遍历
 * 用栈辅助，不用栈的话node节点保留parent
 */


#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <memory>
#include <queue>

using namespace std;

class Node {
public:
    Node(const string &val = "", const std::shared_ptr<Node> left = NULL,  const std::shared_ptr<Node> right = NULL) :
        m_val(val), m_left(left), m_right(right) {}
    string m_val;
    std::shared_ptr<Node> m_left;
    std::shared_ptr<Node> m_right;
};

// 用队列, 层节点先进先出
void TreeLevelVisit(std::shared_ptr<Node> tree_root) {
    std::queue<std::shared_ptr<Node>> node_queue;
    node_queue.push(tree_root);
    while(!node_queue.empty()) {
        auto cur_node = node_queue.front();
        node_queue.pop();
        cout << cur_node->m_val << " ";
        if (cur_node->m_left) {
            node_queue.push(cur_node->m_left);
        }
        if (cur_node->m_right) {
            node_queue.push(cur_node->m_right);
        }
    }
    cout << endl;
}

void TreePreVisit(std::shared_ptr<Node> tree_root) {
    std::stack<std::shared_ptr<Node>> node_stack;
    std::shared_ptr<Node >cur_node = tree_root;
    while (!(cur_node == NULL && node_stack.empty())) {
        while (cur_node) {
            node_stack.push(cur_node);
            cout << cur_node->m_val << " ";
            cur_node = cur_node->m_left;
        }
        auto tmp_node = node_stack.top();
        node_stack.pop();
        cur_node = tmp_node->m_right;
    }
    cout << endl;
}

void TreeMidVisit(std::shared_ptr<Node> tree_root) {
    std::stack<std::shared_ptr<Node>> node_stack;
    std::shared_ptr<Node >cur_node = tree_root;
    while (!(cur_node == NULL && node_stack.empty())) {
        while (cur_node) {
            node_stack.push(cur_node);
            cur_node = cur_node->m_left;
        }
        if (!node_stack.empty()) {
            auto tmp_node = node_stack.top();
            node_stack.pop();
            cout << tmp_node->m_val << " ";
            cur_node = tmp_node->m_right;
        }
    }
    cout << endl;
}

void TreePostVisit(std::shared_ptr<Node> tree_root) {
    std::stack<std::shared_ptr<Node>> node_stack;
    std::shared_ptr<Node>cur_node = tree_root;
    Node *pre_visit_node;
    while (!(cur_node == NULL && node_stack.empty())) {
        while (cur_node) {
            node_stack.push(cur_node);
            cur_node = cur_node->m_left;
        }
        if (!node_stack.empty()) {
            auto tmp_node = node_stack.top();
            node_stack.pop();
            if (tmp_node->m_right && tmp_node->m_right.get() != pre_visit_node) {
                node_stack.push(tmp_node);
                cur_node = tmp_node->m_right;
            }
            else {
                cout << tmp_node->m_val << " ";
                pre_visit_node = tmp_node.get();
            }
        }
    }
    cout << endl;
}

int main() {
    /*
     *            a
     *        b       c
     *      d   e    f   g
     *
     */


    shared_ptr<Node> tree_root(new Node("a"));
    tree_root->m_left = std::make_shared<Node>("b");
    tree_root->m_right = std::make_shared<Node>("c");
    tree_root->m_left->m_left = std::make_shared<Node>("d");
    tree_root->m_left->m_right = std::make_shared<Node>("e");
    tree_root->m_right->m_left = std::make_shared<Node>("f");
    tree_root->m_right->m_right = std::make_shared<Node>("g");

    TreeLevelVisit(tree_root);
    TreePreVisit(tree_root);
    TreeMidVisit(tree_root);
    TreePostVisit(tree_root);

    return 0;
}
