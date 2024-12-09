use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashSet;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn get_dir(dir : char) -> (i32,i32) {
    match dir {
        '>' => (0,1),
        '<' => (0,-1),
        '^' => (-1,0),
        'v' => (1,0),
        _ => (0,0),
    }
}

fn turn_right(dir : char) -> char {
    match dir {
        '>' => 'v',
        '<' => '^',
        '^' => '>',
        'v' => '<',
        _ => 'o',
    }
}

fn in_loop(visited : &HashSet<(i32,i32,char)>, cur_pos : (i32,i32,char), walls : &HashSet<(i32,i32)>, new_wall : (i32,i32), n_row : i32, n_col : i32) -> bool {
    let mut new_visited : HashSet<(i32,i32,char)> = HashSet::new();
    let mut inside : bool = true;
    let mut pos = cur_pos;
    while true {
        new_visited.insert(pos);
        let d = get_dir(pos.2);
        let test_r = pos.0 + d.0;
        let test_c = pos.1 + d.1;
        if test_r < 0 || test_r >= n_row || test_c < 0 || test_c >= n_col {
            return false;
        } else {
            let new_r = test_r;
            let new_c = test_c;
            if walls.contains(&(new_r,new_c)) || (new_r,new_c) == new_wall {
                pos.2 = turn_right(pos.2);
            } else {
                pos.0 = new_r;
                pos.1 = new_c;
            }
        }
        if new_visited.contains(&pos) || visited.contains(&pos) {
            return true;
        }
    }
    return false;
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
    let mut visited : HashSet<(i32,i32)> = HashSet::new();
    let mut visited_loop : HashSet<(i32,i32, char)> = HashSet::new();
    let mut working : HashSet<(i32,i32)> = HashSet::new();
    let mut walls : HashSet<(i32,i32)> = HashSet::new();
    let mut pos : (i32,i32,char) = (0,0,'o');

    let n_row : i32 = char_matrix.len() as i32;
    let n_col : i32 = char_matrix[0].len() as i32;
    let mut start_pos : (i32,i32) = (0,0);
    for r in 0..n_row {
        for c in 0..n_col {
            if char_matrix[r as usize][c as usize] == '#' {
                walls.insert((r,c));
            } else if char_matrix[r as usize][c as usize] == '^' {
                pos = (r,c,'^');
                start_pos = (r,c);
            }
        }
    }
    let mut inside : bool = true;
    while inside {
        visited.insert((pos.0,pos.1));
        visited_loop.insert(pos);
        let d = get_dir(pos.2);
        let test_r = pos.0 + d.0;
        let test_c = pos.1 + d.1;
        if test_r < 0 || test_r >= n_row || test_c < 0 || test_c >= n_col {
            inside = false;
        } else {
            let new_r = test_r;
            let new_c = test_c;
            if walls.contains(&(new_r,new_c)) {
                pos.2 = turn_right(pos.2);
            } else {
                if !working.contains(&(new_r, new_c)) && !visited.contains(&(new_r,new_c)){
                    if in_loop(&visited_loop, pos, &walls , (new_r,new_c), n_row, n_col) {
                        working.insert((new_r,new_c));
                    }
                }
                pos.0 = new_r;
                pos.1 = new_c;
            }
        }
    }
    println!("{:?}",working);
    println!("{:?}",start_pos);
    let ans_a = visited.len() as i64;
    let ans_b = working.len() as i64;
    println!("Answer part A: {}", ans_a);
    println!("Anwer part B: {}", ans_b);
    Ok(())
}
