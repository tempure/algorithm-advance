import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class Main {
    　　　public static void main(String[] args) {
        　　　　　　Scanner sc = new Scanner(System.in);
        　　　　　　int n = sc.nextInt();

        　　　　　　//递归
        　　　　　　　　/*

　　　　　　　　　　Set<String> set=dp(n);
　　　　　　　　　　for (String string : set) {
　　　　　　　　　　　　System.out.println(string);
　　　　　　　　　　}*/

        　　　　　　//正常逻辑
        　　　　　　　　　　Set<String> set = getBracket(n);
        　　　　　　　　　　for (String string : set) {
            　　　　　　　　　　　　System.out.println(string);
            　　　　　　　　　　
        }
        　　
    }

    　　　　private static Set<String> getBracket(int n) {
        　　　　　　　　Set<String> set = new HashSet<String>();
        　　　　　　　　set.add("()");
        　　　　　　　　　　if (n == 1) {
            　　　　　　　　　　　　return set;
            　　　　　　　　　　
        } else {
            　　　　　　　　　　　　for (int i = 1; i < n; i++) {
                　　　　　　　　　　　　　　Set<String> newset = new HashSet<String>();
                　　　　　　　　　　　　　　for (String string : set) {
                    　　　　　　　　　　　　　　　　newset.add("()" + string);
                    　　　　　　　　　　　　　　　　newset.add(string + "()");
                    　　　　　　　　　　　　　　　　newset.add("(" + string + ")");
                    　　　　　　　　　　　　　　
                }
                　　　　　　　　　　　　set = newset;
                　　　　　　　　　　　　
            }
            　　　　　　　　　　　　return set;
            　　　　
        }
    }

    　　　　//递归
    　　　　public static Set<String> dp(int n) {
        　　　　　　　　Set<String> set = new HashSet<String>();
        　　　　　　　　if (n == 1) {
            　　　　　　　　　　set.add("()");
            　　　　　　　　　　return set;
            　　　　　　　　
        } else {
            　　　　　　　　　　Set<String> set2 = dp(n - 1);
            　　　　　　　　　　for (String string : set2) {
                　　　　　　　　　　//左边加
                　　　　　　　　　　　　set.add("()" + string);
                　　　　　　　　　　//右边加
                　　　　　　　　　　　　set.add(string + "()");
                　　　　　　　　　　//包围住
                　　　　　　　　　　　　set.add("(" + string + ")");
                　　　　　　　　　　
            }
            　　　　　　　　　　return set;
            　　　　　　　　　
        }
        　　　　
    }

}