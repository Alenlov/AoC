use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashSet;
use std::collections::HashMap;

#[derive(Eq, Hash, PartialEq, Clone)]
struct Point {
    r: i32,
    c: i32,
}

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn point_within(p : &Point, max_r : i32, max_c : i32) -> bool{
    if p.r < 0 || p.r >= max_r || p.c < 0 || p.c >= max_c {
        return false;
    } else {
        return true;
    }
}

fn antinodes_a(antennas : &HashMap<char,Vec<Point>>, max_row : i32, max_col : i32) -> HashSet<Point>{
    let mut antinodes : HashSet<Point> = HashSet::new();
    for (_, points) in antennas {
        let n = points.len();
        for lhs in 0..n {
            let p1 : &Point = &points[lhs];
            for rhs in 0..lhs {
                let p2 : &Point = &points[rhs];
                // Finns två antinoder per par
                let dr : i32 = p1.r-p2.r;
                let dc : i32 = p1.c-p2.c;
                let anti1 : Point = Point{r:p1.r+dr, c:p1.c+dc};
                let anti2 : Point = Point{r:p2.r-dr, c:p2.c-dc};
                if point_within(&anti1, max_row, max_col) {
                    antinodes.insert(anti1);
                }
                if point_within(&anti2, max_row, max_col) {
                    antinodes.insert(anti2);
                }
            }
        }
    }
    return antinodes;
}

fn antinodes_b(antennas : &HashMap<char,Vec<Point>>, max_row : i32, max_col : i32) -> HashSet<Point>{
    let mut antinodes : HashSet<Point> = HashSet::new();
    for (_, points) in antennas {
        let n = points.len();
        for lhs in 0..n {
            let p1 : &Point = &points[lhs];
            for rhs in 0..lhs {
                let p2 : &Point = &points[rhs];
                // Finns två antinoder per par
                let dr : i32 = p1.r-p2.r;
                let dc : i32 = p1.c-p2.c;
                // From p1
                let mut anti1 = p1.clone();
                while point_within(&anti1, max_row, max_col) {
                    antinodes.insert(anti1.clone());
                    anti1 = Point{r : anti1.r+dr, c : anti1.c+dc};
                }
                // From p2
                let mut anti2 = p2.clone();
                while point_within(&anti2, max_row, max_col) {
                    antinodes.insert(anti2.clone());
                    anti2 = Point{r : anti2.r-dr, c : anti2.c-dc};
                }
            }
        }
    }
    return antinodes;
}

fn main() -> std::io::Result<()>{
    let args: Vec<_> = env::args().collect();
    if args.len() <= 1 {
        return Ok(());
    }
    let mut file = File::open(args[1].clone())?;
    let mut contents = String::new();
    file.read_to_string(&mut contents)?;
    let lines : Vec<&str> = split_lines(&contents);
    let char_matrix : Vec<Vec<char>> = lines.into_iter().map(|line| line.chars().collect()).collect();

    let mut antennas: HashMap<char,Vec<Point>> = HashMap::new();
    let n_row : i32 = char_matrix.len() as i32;
    let n_col : i32 = char_matrix[0].len() as i32;
    for r in 0..n_row {
        for c in 0..n_col {
            let type_char : char = char_matrix[r as usize][c as usize];
            if type_char != '.' {
                if antennas.get(&type_char) == None {
                    antennas.insert(type_char,vec![Point{r:r,c:c}]);
                } else {
                    antennas.get_mut(&type_char).expect("Det blev fel").push(Point{r:r,c:c});
                }
            }
        }
    }
    let antinodes_a = antinodes_a(&antennas, n_row, n_col);
    let ans_a = antinodes_a.len();
    let antinodes_b = antinodes_b(&antennas, n_row, n_col);
    let ans_b = antinodes_b.len();
    println!("Answer part A: {}", ans_a);
    println!("Anwer part B: {}", ans_b);
    Ok(())
}
