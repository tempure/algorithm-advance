# https://blog.csdn.net/weixin_43379056/article/details/86167189
# https://pe.metaquant.org/pe068.html
# 手算最简单。。。
# ans = 6531031914842725

import itertools

class MagicGonRing(object):
    def __init__(self):
        """
        define some variables as class data memebers
        """
        self.gon_ring_type = ''
        self.gon_ring_dict = {'three_gon':6, 'five_gon':10}
        self.S_index_dict  = {'five_gon' :[0, 3, 5, 7, 9], 'three_gon':[0, 3, 5]}              
        #self.T_index_dict  = {'five_gon':[1, 2, 4, 6, 8],'three_gon':[1, 2, 4]}              
        self.Index_dict = {'five_gon' :[0, 1, 2, 3, 2, 4, 5, 4, 6, 7, 6, 8, 9, 8, 1],
                           'three_gon':[0, 1, 2, 3, 2, 4, 5, 4, 1]}

    def checkClockwiseWorking(self, digits_list):    
        """
        check clockwise working
        """
        for index in self.S_index_dict[self.gon_ring_type]:
            if digits_list[0] > digits_list[index]:
                return False
        return True

    def checkSumOfGonRing(self, digits_list):
        """
        check each gon sum of three numbers, 
        if all are equal, return value of one gon sum, else return 0
        """
        gon_1_sum, one_gon_sum = 0, 0

        for i, index in enumerate(self.Index_dict[self.gon_ring_type]):
            one_gon_sum += digits_list[index]
            if (i+1) % 3 == 0:
                if i == 2:
                    gon_1_sum = one_gon_sum
                else:
                    if gon_1_sum != one_gon_sum: 
                        return 0
                one_gon_sum = 0
        return gon_1_sum

    def updateGonRingSolutionsDict(self, digits_list, gon_ring_solutions_dict):
        """
        update gon_ring_solutions_dict according to permutated digits list
        """
        if True == self.checkClockwiseWorking(digits_list):
            one_gon_sum = self.checkSumOfGonRing(digits_list)
            if one_gon_sum > 0:
                solution_set_list = []
                for i in self.Index_dict[self.gon_ring_type]:
                    solution_set_list += [ digits_list[i] ]
                
                solution_str = ''.join(list(map(str, solution_set_list)))
                
                if one_gon_sum not in gon_ring_solutions_dict.keys():
                    gon_ring_solutions_dict[one_gon_sum]  = [ solution_str ]
                else:
                    gon_ring_solutions_dict[one_gon_sum] += [ solution_str ]

    def findMaximumString(self, gon_ring_type):
        """
        gon type: 'three_gon' or 'five_gon'
        """
        self.gon_ring_type, n = gon_ring_type, self.gon_ring_dict[gon_ring_type]
        
        # create digits list for 3-gon ring or 5-gon ring
        digits_list = [ i for i in range(1, n+1) ]   
    
        gon_ring_solutions_dict = {}

        for term in itertools.permutations(digits_list):
            self.updateGonRingSolutionsDict(term, gon_ring_solutions_dict)

        # print(gon_ring_solutions_dict)   # print all solutions for debug 
    
        gon_ring_solutions_list = []
        for solution_set_list in gon_ring_solutions_dict.values():
            gon_ring_solutions_list += solution_set_list
            
        for solution_str in sorted(gon_ring_solutions_list)[::-1]: # reverse
            if gon_ring_type == 'three_gon' :   # 3-gon ring
                return solution_str
            else:                               # 5-gon ring 
                # find maximum 16-digit string for a "magic" 5-gon ring
                if len(solution_str) == 16: return solution_str
        
def main():
    magic_gon_ring = MagicGonRing()
            
    assert '432621513' == magic_gon_ring.findMaximumString('three_gon')

    print("The maximum 16-digit string for a \"magic\" 5-gon ring is %s." %
          magic_gon_ring.findMaximumString('five_gon'))
    
if  __name__ == '__main__':
    main()