TreeNode* buildTree(TreeNode* parent, vector<int> inputTree, int idx, int n, int depth, vector<int>& blueInDepth) {
  if(idx >= n) {
    return nullptr;
  }

  cout << "Index: " << idx  << " Depth: " << depth << endl;

  int color = inputTree[idx];
  TreeNode* newNode = new TreeNode(idx, color);
  newNode->parent = parent;

  if(depth == blueInDepth.size()) {
    if(color == BLUE) {
      blueInDepth.push_back(1);
    }else {
      blueInDepth.push_back(0);
    }
  } else {
    if(color == BLUE) {
      blueInDepth[depth] = blueInDepth[depth] + 1;
    }
  }

  // for(int i = 0; i < blueInDepth.size(); i++) {
  //   cout << blueInDepth[i] << " ";
  // }

  // cout << endl;

  int leftIdx = (idx * 2) + 1 - (blueInDepth[depth] * 2);
  int rightIdx = (idx * 2) + 2 - (blueInDepth[depth] * 2);

  // cout << "   Left idx: " << leftIdx << endl;
  // cout << "   Right idx: " << rightIdx << endl;

  if(color == BLUE) {
    newNode->left = nullptr;
    newNode->right = nullptr;

  } else {
    newNode->left = buildTree(newNode, inputTree, leftIdx, n, depth + 1, blueInDepth);
    newNode->right = buildTree(newNode, inputTree, rightIdx, n, depth + 1, blueInDepth);
  }

  return newNode;
}