package org.example;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String str = sc.next();
        int[] cnt = new int[30];
        for (int i = 0; i < str.length(); i++) {
            int t = str.charAt(i) - 'a';
            cnt[t]++;
        }
        for (int i = 0; i < str.length(); i++) {
            int t = str.charAt(i) - 'a';
            if (cnt[t] == 1) {
                System.out.println(str.charAt(i));
                return;
            }
        }
        System.out.println("no");
    }
}