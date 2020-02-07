# Keep the function signature,                                                                        
# but replace its body with your implementation                                                       

import os
import sys
import zlib

class CommitNode:
    def __init__(self, commit_hash):
        """
        :type commit_hash: str
        """
        self.commit_hash = commit_hash
        self.parents = set()
        self.children = set()
        self.indegrees = 0

def dfs(leaf, nodes):
	s = []
	# create leaf node
	if leaf not in nodes:
		leaf_node = CommitNode(leaf)
		nodes.update({leaf : leaf_node})
		s.append(leaf)
	# dfs
	s.append(leaf)
	while len(s) != 0:
		v = s[-1]
		s.pop()
		folder = v[0:2]
		file = v[2:]
		full = os.getcwd() + "/.git/objects/" + folder + "/" + file
		compressed_contents = open(full, 'rb').read()
		decompressed_contents = zlib.decompress(compressed_contents)
		decoded_contents = decompressed_contents.decode("utf-8", "ignore").split()
		i = 0
		f_children = []
		while not decoded_contents[i] == "author":
			if decoded_contents[i] == "parent":
				f_children.append(decoded_contents[i+1])
			i+=1

		# loops through children and adds it to current vertex' parent
		for f_child in f_children:
			nodes[v].parents.add(f_child)

		# loops through children, if node not existent, make node and add to stack
		# if exists, simply add current vertex to existing children set
		for f_child in f_children:
			if f_child not in nodes:
				s.append(f_child)
				new_node = CommitNode(f_child)
				new_node.children.add(v)
				nodes.update({f_child : new_node})
			else:
				nodes[f_child].children.add(v)

def topo_sort(root, nodes, sorted_commits):
	queue = []
	for n in nodes:
		nodes[n].indegrees = len(nodes[n].children)
		if nodes[n].indegrees == 0:
			queue.append(n)
	while queue:
		v = queue.pop(0)
		sorted_commits.append(v)
		for parent in sorted(nodes[v].parents):
			nodes[parent].indegrees-=1
			if nodes[parent].indegrees == 0:
				queue.append(parent)



def print_sorted(sorted_commits, nodes, branches):
	last_commit = ""
	first = True
	for commit in sorted_commits:
		if commit in branches:
			branch_name = " " + branches[commit]
		else:
			branch_name = ""

		if first:
			print(commit + branch_name)
			last_commit = commit			
			first = False
		elif last_commit not in nodes[commit].children:
			space = False
			for parent in sorted(nodes[last_commit].parents):
				if space:
					print(" ", end="")
				print(parent, end="")
				space = True
			print("=")
			print("")
			print("=", end="")
			space = False
			for child in sorted(nodes[commit].children):
				if space:
					print(" ", end="")
				print(child, end="")
				space = True
			print("")
			print(commit + branch_name)
			last_commit = commit
		else:
			print(commit + branch_name)
			last_commit = commit
		


def topo_order_commits():
    while not os.path.isdir('.git'):
        os.chdir('..')
        if(os.getcwd() == '/'):
            sys.stderr.write("Not inside a Git repository")
            sys.exit(1)
    os.chdir('.git/refs/heads')
    branch_names = os.listdir(os.getcwd());    
    os.chdir('../../..')
    branches = []
    branch_dict = dict()
    nodes = dict()
    for x in branch_names:
    	path = os.getcwd() + "/.git/refs/heads/" + x
    	content = open(path, 'rb').read().decode("utf-8")
    	branches.append(content[:-1])
    	if content[:-1] not in branch_dict:
    		branch_dict.update({content[:-1] : x})
    	else:
    		branch_dict[content[:-1]] = branch_dict[content[:-1]] + " " + x
    	

    # generate tree
    for x in branches:
    	dfs(x,nodes)

    # find root
    for n in nodes:
    	if not nodes[n].parents:
    		root = n

    # topological sort of commit tree
    sorted_commits = []
    topo_sort(root, nodes, sorted_commits)

    # print output
    print_sorted(sorted_commits, nodes, branch_dict)
    #print(root)



    


if __name__ == '__main__':
    topo_order_commits()