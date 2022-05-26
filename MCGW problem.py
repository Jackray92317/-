# MCGW Problem

def genStates():
    '''
    Input: no input needed in this function.
    Output: output all the possible states of the node of mcgw_problem. 
    The function is to generate all the states in lexicographical order.
    '''
    side = ("E", "W") # the nodes symbol east and west
    states = []
    for i in side:
        for j in side:
            for k in side:
                for l in side:
                    aState = i + j + k + l
                    states.append(aState)
    return states

def isLegal(state):
    '''
    Input: all the states generate from genStates()
    Output: the legalstates that meet the reqeust of the mcgw_problem.
    The fuction is to find out the legalstates of the mcgw_problem.
    '''
    # The if() statement expresses the condition for illegal state
    if (state[1] == state[2] or state[2] == state[3]) and state[0] != state[2]:
        return False
    else:
        return True

legalStates = [] # void list to restore legal states
allStates = genStates()
for state in allStates:
    if isLegal(state):
        legalStates.append(state)

from collections import defaultdict # a module for generating the graph


graph = defaultdict(list) # create a void dict as a graph

def addEdge(graph,u,v):
    '''
    Input: a void graph, a node to be the key, a node to be the values.
    No output
    The function is to create and link the keys and the values in the graph.
    '''
    graph[u].append(v)

def Gengraph(states):
    '''
    Input: the legal states to use for general the graph.
    No output but generate the graph through the function addEdge().
    The function is to generate the graph through links.
    '''
    # Down are the way to create the link(neighbor) of the mcgw_problem
    for i in range(len(states)):
        if states[i][0] == 'E':
            for state in states:
                change = 0
                if state[0] == 'W':
                    if state[1] != states[i][1]:
                        change += 1
                    if state[2] != states[i][2]:
                        change += 1
                    if state[3] != states[i][3]:
                        change += 1
                    if change == 1:
                        addEdge(graph,states[i],state)
        elif states[i][0] == 'W':
            for state in states:
                change = 0
                if state[0] == 'E':
                    if state[1] != states[i][1]:
                        change += 1
                    if state[2] != states[i][2]:
                        change += 1
                    if state[3] != states[i][3]:
                        change += 1
                    if change == 1 or change == 0:
                        addEdge(graph,states[i],state)

Gengraph(legalStates)

def findSP(graph, src, dest):
        '''
        Input: the graph that we need to find out the shortest path which is also
        a correct path of the problem. a starting node stands for src and a destination
        code stands for dest, which are the start and the end of the graph
        Output: a list which is the shortest path of the graph
        The function is to find out the shortest path
        '''
        queue = [src] # the place to restore the same depth level code while doing bfs
        visited = [src] # the place to restore the searched nodes
        bfs_Tree = {src:src} # to made bfs_tree
        path = [] # the initial list for the final output

        while queue:
                s = queue.pop(0)

                for neighbor in graph[s]:
                        if neighbor not in visited:
                                queue.append(neighbor)
                                visited.append(neighbor) # for the while loop is the process for bfs
                                bfs_Tree.update({neighbor:s}) # for the bfs_tree
        path = [dest]
        last = dest
        while src not in path:
                v = bfs_Tree.get(last)
                path.append(v)
                last = v # using the bfs_tree to search for the shortest path
        return path


def meaning(node1, node2):
        '''
        Input: the nodes which is searching for the meaning and a previous node
        for help determining the meaning by finding the difference for before and after.
        Output: the words for what they done crossing the river.
        The function is to translate the nodes to the words.
        '''
        if node1[1] != node2[1]:
            if node1[0] == 'E':
                return 'The man takes the cabbage to the east.'
            elif node1[0] == 'W':
                return 'The man takes the cabbage to the west.'
        if node1[2] != node2[2]:
            if node1[0] == 'E':
                return 'The man takes the goat to the east.'
            elif node1[0] == 'W':
                return 'The man takes the goat to the west.'
        if node1[3] != node2[3]:
            if node1[0] == 'E':
                return 'The man takes the wolf to the east.'
            elif node1[0] == 'W':
                return 'The man takes the wolf to the west.'
        if node1[0] != node2[0] and node1[1] == node2[1] and node1[2] == node2[2] and node1[3] == node2[3]:
            if node1[0] == 'E':
                return 'The man takes himself to the east.'
            elif node1[0] == 'W':
                return 'The man takes himself to the west.'

def main():
        path = findSP(graph, 'EEEE','WWWW')
        list.reverse(path) # the path is upside down while being return from the function of findSP.
        for i in range(1,len(path)): # translating and printing the result.
                done = meaning(path[i],path[i-1])
                print("{:}. {:}".format(i,done))

main()
