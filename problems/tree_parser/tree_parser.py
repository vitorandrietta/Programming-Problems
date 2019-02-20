def left_node_last_index (opening_char, closing_char, str):
    unclosed_terminators = 0 
    for i,c in zip(range(0,len(str)),str):
        if c == opening_char:
            unclosed_terminators += 1
        elif c == closing_char:
            unclosed_terminators -=1
        if unclosed_terminators == 0:
            return i
        
    

class Node:
    def __init__(self, value, left=None, right=None):
        self.left = left
        self.right = right
        self.value = value

class Tree:
    def __init__(self,root):
        self.root = root

    #tree object parsed to form, eg:(root(firts_left_child()())(first_right_shield()()))    
    def __str__(self):
        return self.tree_str(self.root)
    
    def tree_str(self, root):
        if not root :
            return "()"
        left_node = self.tree_str(root.left)
        right_node = self.tree_str(root.right)
        str_node = "".join(["(", root.value.__str__(), left_node, right_node, ")"])
        return str_node
    
    def str_to_tree(self, str):
        if str == "()":
            return  None
      
        str = str[1:-1]
        node_value = str[0:str.index("(")]
        node_value_len = len(node_value)
        str = str[node_value_len:]
        left_node_end = left_node_last_index("(",")",str)
        left_node  = self.str_to_tree(str[0:left_node_end+1])
        right_node = self.str_to_tree(str[left_node_end+1:])

        return Node(node_value,left_node,right_node)
