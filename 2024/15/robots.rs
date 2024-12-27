use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashSet;
use std::collections::VecDeque;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

fn get_dir(d : char) -> (i32,i32) {
    match d {
        'v' => (1,0),
        '>' => (0,1),
        '^' => (-1,0),
        '<' => (0,-1),
        _ => (0,0),
    }
}

fn plot_map(robot : (i32,i32), walls : HashSet<(i32,i32)>, crates : HashSet<(i32,i32)>, max_r : i32, max_c : i32) {
    for r in 0..max_r {
        for c in 0..max_c {
            if walls.contains(&(r,c)) {
                print!("#");
            } else if crates.contains(&(r,c)) {
                print!("O");
            } else if robot == (r,c) {
                print!("@");
            } else {
                print!(" ");
            }
        }
        print!("\n");
    }
}

fn plot_map_b(robot : (i32,i32), walls : HashSet<(i32,i32)>, crates_l : HashSet<(i32,i32)>, crates_r : HashSet<(i32,i32)>, max_r : i32, max_c : i32) {
    for r in 0..max_r {
        for c in 0..2*max_c {
            if walls.contains(&(r,c)) {
                print!("#");
            } else if crates_l.contains(&(r,c)) {
                print!("[");
            } else if crates_r.contains(&(r,c)) {
                print!("]");
            } else if robot == (r,c) {
                print!("@");
            } else {
                print!(".");
            }
        }
        print!("\n");
    }
}

fn can_move(robot : (i32,i32), d : char, walls : HashSet<(i32,i32)>, crates : HashSet<(i32,i32)>) -> (bool, (i32,i32)) {
    let first_empty : (i32,i32) = (0,0);
    let dir = get_dir(d);
    let mut found_wall : bool = false;
    let mut new_pos = robot;
    while !found_wall {
        new_pos = (new_pos.0 + dir.0, new_pos.1 + dir.1);
        if walls.contains(&new_pos) {
            found_wall = true;
        } else if !crates.contains(&new_pos) {
            return (true, new_pos);
        }
    }

    return (false, first_empty);
}

fn can_move_b(robot : (i32,i32), d : char, walls : HashSet<(i32,i32)>, crates_l : HashSet<(i32,i32)>, crates_r : HashSet<(i32,i32)>) -> bool {
    //println!("{:?}", robot);
    let dir = get_dir(d);
    let new_pos = (robot.0 + dir.0, robot.1 + dir.1);
    if walls.contains(&new_pos) {
        return false;
    } else if crates_l.contains(&new_pos) {
        if (d == 'v') || (d == '^') {
            let move_l : bool = can_move_b(new_pos, d, walls.clone(), crates_l.clone(), crates_r.clone());
            let move_r : bool = can_move_b((new_pos.0,new_pos.1+1), d, walls.clone(), crates_l.clone(), crates_r.clone());
            return move_l && move_r;
        } else {
            return can_move_b(new_pos, d, walls.clone(), crates_l.clone(), crates_r.clone());
        }
    } else if crates_r.contains(&new_pos) {
        if (d == 'v') || (d == '^') {
            let move_l : bool = can_move_b((new_pos.0,new_pos.1-1), d, walls.clone(), crates_l.clone(), crates_r.clone());
            let move_r : bool = can_move_b(new_pos, d, walls.clone(), crates_l.clone(), crates_r.clone());
            return move_l && move_r;
        } else {
            return can_move_b(new_pos, d, walls.clone(), crates_l.clone(), crates_r.clone());
        }
    } else {
        return true;
    }

    return false;
}

fn move_crates(start_pos : (i32,i32), d : char, mut crates_l : HashSet<(i32,i32)>, mut crates_r : HashSet<(i32,i32)>) -> (HashSet<(i32,i32)>, HashSet<(i32,i32)>) {
    let mut to_move : VecDeque<(i32,i32)> = VecDeque::new();
    let mut new_crates_l : HashSet<(i32,i32)> = HashSet::new();
    let mut new_crates_r : HashSet<(i32,i32)> = HashSet::new();
    let dir : (i32,i32) = get_dir(d);
    to_move.push_back(start_pos);
    while !to_move.is_empty() {
        let pos = to_move.pop_front().unwrap();
        if crates_l.contains(&pos) {
            // ta bort från l och r. Flytta cích lägg i new
            // Lägg till nya platserna i to_move
            crates_l.remove(&pos);
            crates_r.remove(&(pos.0, pos.1+1));
            new_crates_l.insert((pos.0+dir.0,pos.1+dir.1));
            new_crates_r.insert((pos.0+dir.0,pos.1+1+dir.1));
            to_move.push_back((pos.0+dir.0,pos.1+dir.1));
            to_move.push_back((pos.0+dir.0,pos.1+1+dir.1));
        } else if crates_r.contains(&pos) {
            crates_l.remove(&(pos.0,pos.1-1));
            crates_r.remove(&pos);
            new_crates_l.insert((pos.0+dir.0,pos.1-1+dir.1));
            new_crates_r.insert((pos.0+dir.0,pos.1+dir.1));
            to_move.push_back((pos.0+dir.0,pos.1-1+dir.1));
            to_move.push_back((pos.0+dir.0,pos.1+dir.1));
        }
    }
    for cl in new_crates_l {
        crates_l.insert(cl);
    }
    for cr in new_crates_r {
        crates_r.insert(cr);
    }
    return (crates_l, crates_r);
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
    
    let mut crates : HashSet<(i32,i32)> = HashSet::new();
    let mut walls : HashSet<(i32,i32)> = HashSet::new();
    let mut robot : (i32,i32) = (0,0);
    let mut crates_b_l : HashSet<(i32,i32)> = HashSet::new();
    let mut crates_b_r : HashSet<(i32,i32)> = HashSet::new();
    let mut walls_b : HashSet<(i32,i32)> = HashSet::new();
    let mut robot_b : (i32,i32) = (0,0);

    let mut r : i32 = 0;
    let mut max_c : i32 = 0;

    let mut instructions : Vec<Vec<char>> = Vec::new();

    for line in lines {
        if line.len() == 0 {
            continue;
        } else {
            let row : Vec<char> = line.chars().collect();
            if row[0] == '#' {
                if max_c == 0 {
                    max_c = row.len() as i32;
                }
                for c in 0..max_c {
                    if row[c as usize] == '#' {
                        walls.insert((r,c));
                        walls_b.insert((r,2*c));
                        walls_b.insert((r,2*c+1));
                    } else if row[c as usize] == 'O' {
                        crates.insert((r,c));
                        crates_b_l.insert((r,2*c));
                        crates_b_r.insert((r,2*c+1));
                    } else if row[c as usize] == '@' {
                        robot = (r,c);
                        robot_b = (r,2*c);
                    }
                }
                r += 1;
            } else {
                instructions.push(row);
            }
        }
    }

    let mut ans_a: u64 = 0;
    let mut ans_b: u64 = 0;
    //println!("Num walls: {}, Num crates: {}, Robot = {:?}, rows = {}, cols = {}",walls.len(), crates.len(), robot, r, max_c);
    
    //plot_map(robot, walls.clone(), crates.clone(), r, max_c);

    //plot_map_b(robot_b, walls_b.clone(), crates_b_l.clone(), crates_b_r.clone(), r, max_c);

    for inst in instructions {
        for d in inst {
            let (c, p) = can_move(robot, d, walls.clone(), crates.clone());
            if c {
                robot.0 += get_dir(d).0;
                robot.1 += get_dir(d).1;
                if crates.contains(&robot) {
                    crates.remove(&robot);
                    crates.insert(p);
                }
            }
            if can_move_b(robot_b, d, walls_b.clone(), crates_b_l.clone(), crates_b_r.clone()) {
                robot_b.0 += get_dir(d).0;
                robot_b.1 += get_dir(d).1;
                (crates_b_l, crates_b_r) = move_crates(robot_b, d, crates_b_l.clone(), crates_b_r.clone());
            }
            //println!("After instruction {}",d);
            //plot_map_b(robot_b, walls_b.clone(), crates_b_l.clone(), crates_b_r.clone(), r, max_c);
        }
    }

    for cr in crates {
        ans_a += (cr.0 * 100 + cr.1) as u64;
    }
    for cl in crates_b_l {
        ans_b += (cl.0 * 100 + cl.1) as u64;
    }

    println!("Answer part A: {}", ans_a);
    
    println!("Answer part B: {}", ans_b);
    Ok(())
}
