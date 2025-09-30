[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/T_SwjO2j)
# Identity
Name : M. Ilfi Faza Nasibi

# AI usage
Saya menggunakan AI untuk menghasilkan proyek Qt Creator.
AI yang Digunakan: Gemini

Kueri yang digunakan:
Create an application with
● A canvas
● Run Convex Hull Button
● Clear Button
● The canvas will served both as drawing canvas and final
convex hull drawing
● Clear button will simply clear canvas

Our UI
Main Window
● Central Widget
● QVbox Layout
● Drawing Widget
● QboxLayout
● RunSimulationButton
● ClearButton

● Implement both slow convex hull and convex hull algorithm
● Track how many iteration in general taken using the same
dataset
● Wrote the iteration number on canvas

Algorithm SLOWCONVEXHULL(P)
Input. A set P of points in the plane.
Output. A list L containing the vertices of CH(P) in clockwise order.

1. E ← /0.
2. for all ordered pairs (p,q) ∈ P×P with p not equal to q
3. do valid ← true
4. for all points r ∈ P not equal to p or q
5. do if r lies to the left of the directed line from p to q
6. then valid ← false.
7. if valid then Add the directed edge → pq to E.
8. From the set E of edges construct a list L of vertices of CH(P), sorted in clockwise order.

Algorithm CONVEXHULL(P)
Input. A set P of points in the plane.
Output. A list containing the vertices of CH(P) in clockwise order.

1. Sort the points by x-coordinate, resulting in a sequence p1,..., pn.
2. Put the points p1 and p2 in a list Lupper, with p1 as the first point.
3. for i ← 3 to n
4. do Append pi to Lupper.
5. while Lupper contains more than two points and the last three points in Lupper do not make a right turn
6. do Delete the middle of the last three points from Lupper.
7. Put the points pn and pn−1 in a list Llower 6 , with pn as the first point.
8. for i ← n−2 downto 1
9. do Append pi to Llower.
10. while Llower contains more than 2 points and the last three points in Llower do not make a right turn
11. do Delete the middle of the last three points from Llower.
12. Remove the first and the last point from Llower to avoid duplication of the points where the upper and lower hull meet.
13. Append Llower to Lupper, and call the resulting list L.
14. return L

Create on Qt Creator

# Collaboration usage
Tugas ini diselesaikan sepenuhnya oleh saya sendiri dengan memanfaatkan AI sebagai alat bantu. Tidak ada orang lain yang terlibat dalam proses ini. Seluruh alur kerja terdiri dari merumuskan prompt yang detail, memberikannya kepada AI, dan mengintegrasikan kode yang dihasilkan ke dalam proyek Qt Creator. Saya tidak menyalin dari mahasiswa lain, juga tidak menerima ide atau strategi implementasi dari siapa pun. Adaptasi dan penggunaan AI dilakukan secara mandiri.

# Commit Rules
Use .gitignore to stripe any binaries from the resulting build before commit.  If you cloned directly from the template, you are safe. 

# Due Time
September 30th, 2025. 23: 59 WIB
