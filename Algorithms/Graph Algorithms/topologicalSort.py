import os
import sys
import zlib


#I use Kahn's algorithm from Wikipedia. Mutates the graph, but produces desired output
def get_topo_ordered_commits (commit_nodes, root_hashes):
    
    l = []
    s = []
    for i in sorted(root_hashes):
        s.append(i)

    while s:
        cur = s.pop()
        l.append(commit_nodes[cur])
        for child in sorted(commit_nodes[cur].children.copy()):
            commit_nodes[cur].children.remove(child)
            commit_nodes[child].parents.remove(cur)
            if len(commit_nodes[child].parents) == 0:
                s.append(child)
    
    return l




class CommitNode:
    def __init__(self, commit_hash):
        """
        :type commit_hash: str
        """
        self.commit_hash = commit_hash
        self.parents = set()
        self.children = set()
    
    def __eq__(self, other):
        return self.commit_hash == other.commit_hash





def get_git():
    b = os.getcwd()
    while True:
        a = os.listdir(b)
        for i in a:
            if i == ".git":
                if b != "/":    
                    return b + "/" + i
                else:
                    return b+i      
        if b == "/":
            sys.stderr.write("Not inside a Git repository\n")
            sys.exit(1)
        b = os.path.dirname(b)


def get_branches(x):
    x = x + "/refs/heads"
    dict = {}

    for (root,dirs,files) in os.walk(x, topdown=True): 
        for i in files:
            with open(root+ "/" + i, "r") as file:
                data = file.read().replace('\n', '')
            dict[root+ "/" + i] = data
    return dict


def build_commit_graph(dict):
    
    #.git/objects
    obj_dir = get_git() + "/objects"

    all_commits = {}
    all_roots = {}
    stack = []
    for i in dict:
        stack.append(dict[i])

    while (stack): 
        commit_id = stack.pop()
        first_two = commit_id[0:2]
        last_thirty_eight = commit_id[2:]
        #.git/objects/12
        hash_dir = obj_dir + "/" + first_two + "/" + last_thirty_eight
        all_commits[commit_id] = CommitNode(commit_id) 

        compressed_contents = open(hash_dir, 'rb').read()
        decompressed_contents = zlib.decompress(compressed_contents)
        decoded = decompressed_contents.decode(encoding = "UTF-8", errors="ignore")

        if "commit" in decoded:
            if "parent" in decoded:
                a = decoded.split("\n")
                for iter in a:
                        if(iter.startswith("parent")):
                            parent_hash = iter[7:]
                            all_commits[commit_id].parents.add(parent_hash)
                            stack.append(parent_hash)

    for i in all_commits:
        for par_id in all_commits[i].parents:
            all_commits[par_id].children.add(i)

    for i in all_commits:
        if (len(all_commits[i].parents) == 0):
            all_roots[i] = all_commits[i]

    

    return all_commits, all_roots
    


def print_topo_ordered_commits_with_branch_names(commit_nodes, topo_ordered_commits, head_to_branches):
    jumped = False
    for i in range(len(topo_ordered_commits)):
        commit_hash = topo_ordered_commits[i]
        if jumped:
            jumped = False
            sticky_hash = ' '.join(sorted(commit_nodes[commit_hash].children))
            print(f'={sticky_hash}')
        branches = (head_to_branches[commit_hash]) if commit_hash in head_to_branches else []
        #print(branches)
        print(commit_hash + (' '  + (branches) if branches else ''))
        if i+1 < len(topo_ordered_commits) and topo_ordered_commits[i+1] not in commit_nodes[commit_hash].parents:
            jumped = True
            sticky_hash = ' '.join(sorted(commit_nodes[commit_hash].parents))
            print(f'{sticky_hash}=\n')
        







x = get_git()
dict = get_branches(x)
all_commits, all_roots = build_commit_graph(dict)

commit_nodes = {}
root_nodes = {}

for i in all_commits:
    commit_nodes[i] = CommitNode(i)
    for child in all_commits[i].children:
        commit_nodes[i].children.add(child)
    for parent in all_commits[i].parents:
        commit_nodes[i].parents.add(parent)


for i in all_roots:
    root_nodes[i] = all_roots[i]



l = get_topo_ordered_commits(all_commits, all_roots)

topo_ordered_commits = []
for i in l:
    topo_ordered_commits.append(i.commit_hash)
topo_ordered_commits.reverse()


head_to_branches = {}

for i in dict:
    str = i.split("refs/heads/",1)[1] 
    head_to_branches[dict[i]] = str

#for i in head_to_branches:
#   print(i + "     " + head_to_branches[i])

print_topo_ordered_commits_with_branch_names(commit_nodes, topo_ordered_commits, head_to_branches)
"""
for i in commit_nodes:
    b = len(commit_nodes[i].children)
    if b == 0:
        print(i)
    for a in commit_nodes[i].children:
        print(i + "        " + a)
"""



#for i in l:
#   print(i.commit_hash)
