use std::env;
use std::vec::Vec;
use std::fs::File;
use std::io::prelude::*;
use std::collections::HashMap;
use std::collections::HashSet;
use std::collections::VecDeque;

fn split_lines(basic_line: &str) -> Vec<&str> {
    basic_line
        .trim()
        .split("\n")
        .collect()
}

// #[derive(Copy, Clone, Eq, PartialEq)]
// struct State {
//     state: [char;3],
//     inputs: usize,
// }


fn move_directional(cur: char, input: char) -> Option<char> {
    match cur {
        '<' => {
            return match input {
                '>' => Some('v'),
                _ => None::<char>,
            };
        },
        '>' => {
            return match input {
                '^' => Some('A'),
                '<' => Some('v'),
                _ => None::<char>,
            };
        },
        'v' => {
            return match input {
                '^' => Some('^'),
                '<' => Some('<'),
                '>' => Some('>'),
                _ => None::<char>,
            };
        },
        '^' => {
            return match input {
                'v' => Some('v'),
                '>' => Some('A'),
                _ => None::<char>,
            };
        },
        'A' => {
            return match input {
                'v' => Some('>'),
                '<' => Some('^'),
                _ => None::<char>,
            };
        },
        _ => None::<char>,
    };
    return None::<char>
}

fn move_keypad(cur: char, input: char) -> Option<char> {
    match cur {
        'A' => {
            return match input {
                '>' => None::<char>,
                '<' => Some('0'),
                '^' => Some('3'),
                'v' => None::<char>,
                _ => None::<char>,
            };
        },
        '0' => {
            return match input {
                '>' => Some('A'),
                '<' => None::<char>,
                '^' => Some('2'),
                'v' => None::<char>,
                _ => None::<char>,
            };
        },
        '1' => {
            return match input {
                '>' => Some('2'),
                '<' => None::<char>,
                '^' => Some('4'),
                'v' => None::<char>,
                _ => None::<char>,
            };
        },
        '2' => {
            return match input {
                '>' => Some('3'),
                '<' => Some('1'),
                '^' => Some('5'),
                'v' => Some('0'),
                _ => None::<char>,
            };
        },
        '3' => {
            return match input {
                '>' => None::<char>,
                '<' => Some('2'),
                '^' => Some('6'),
                'v' => Some('A'),
                _ => None::<char>,
            };
        },
        '4' => {
            return match input {
                '>' => Some('5'),
                '<' => None::<char>,
                '^' => Some('7'),
                'v' => Some('1'),
                _ => None::<char>,
            };
        },
        '5' => {
            return match input {
                '>' => Some('6'),
                '<' => Some('4'),
                '^' => Some('8'),
                'v' => Some('2'),
                _ => None::<char>,
            };
        },
        '6' => {
            return match input {
                '>' => None::<char>,
                '<' => Some('5'),
                '^' => Some('9'),
                'v' => Some('3'),
                _ => None::<char>,
            };
        },
        '7' => {
            return match input {
                '>' => Some('8'),
                '<' => None::<char>,
                '^' => None::<char>,
                'v' => Some('4'),
                _ => None::<char>,
            };
        },
        '8' => {
            return match input {
                '>' => Some('9'),
                '<' => Some('7'),
                '^' => None::<char>,
                'v' => Some('5'),
                _ => None::<char>,
            };
        },
        '9' => {
            return match input {
                '>' => None::<char>,
                '<' => Some('8'),
                '^' => None::<char>,
                'v' => Some('6'),
                _ => None::<char>,
            };
        },
        _ => None::<char>,
    };
    return None::<char>
}

// fn update_state(cur: [char;3], input: char) -> Option<[char;3]> {
//     // Move 0
//     let mut inpu1: char = '0';
//     let mut new = cur;
//     if input != 'A' {
//         let new_0 = move_directional(cur[0], input);
//         if !new_0.is_none() {
//             new[0] = new_0.unwrap();
//         } else {
//             return None;
//         }
//     } else {
//         if cur[0] != 'A' {
//             let new_1 = move_directional(cur[1], cur[0]);
//             if !new_1.is_none() {
//                 new[1] = new_1.unwrap();
//             } else {
//                 return None;
//             }
//         } else {
//             if cur[1] != 'A' {
//                 let new_2 = move_keypad(cur[2], cur[1]);
//                 if !new_2.is_none() {
//                     new[2] = new_2.unwrap();
//                 } else {
//                     return None;
//                 }
//             }
//         }
//     }

//     return Some(new)
// }


// fn find_shortest(start: char) -> HashMap<char,usize> {
//     let inputs = ['<', '>', 'v', '^', 'A'];
//     let start_v = ['A','A',start];
//     let mut heads: VecDeque<State> = VecDeque::new();
//     let mut visited: HashSet<[char;3]> = HashSet::new();
//     heads.push_back(State{state: start_v, inputs: 0});
//     let mut ends: HashMap<char,usize> = HashMap::new();
//     while let Some(h) = heads.pop_front() {
//         visited.insert(h.state);
//         for input in inputs {
//             if input == 'A' && h.state[0] == 'A' && h.state[1] == 'A' {
//                 let output = h.state[2];
//                 if !ends.contains_key(&output) {
//                     ends.insert(output, h.inputs+1);
//                 }
//             } else {
//                 let new_h_state = update_state(h.state, input);
//                 if !new_h_state.is_none() {
//                     if !visited.contains(&new_h_state.unwrap()) {
//                         heads.push_back(State{state: new_h_state.unwrap(), inputs: h.inputs + 1});
//                     }
//                 }
//             }
//         }
//     }
//     return ends
// }

fn find_steps_directional(start: char) -> HashMap<char,Vec<char>> {
    let inputs = ['<','v','^','>','A'];
    let mut heads: VecDeque<(char,Vec<char>)> = VecDeque::new();
    let mut visited: HashSet<char> = HashSet::new();
    heads.push_back((start, Vec::new()));
    let mut ends: HashMap<char,Vec<char>> = HashMap::new();
    while let Some(h) = heads.pop_front() {
        visited.insert(h.0);
        for input in inputs {
            let mut new_vec: Vec<char> = h.1.clone();
            if new_vec.len() > 0 {
                let last_in = new_vec[ new_vec.len() - 1 ];
                if last_in != input && new_vec.len() > 1 {
                    if input == new_vec[0] {
                        continue
                    }
                }
            }
            new_vec.push(input);
            if input == 'A' {
                if !ends.contains_key(&h.0){
                    ends.insert(h.0, new_vec);
                }
            } else {
                let new_h = move_directional(h.0, input);
                if !new_h.is_none(){
                    if !visited.contains(&new_h.unwrap()) {
                        heads.push_back((new_h.unwrap(), new_vec));
                    }
                }
                
            }
        }
    }
    return ends;
}

fn combine_steps(dirs_map: &HashMap<(char,char),Vec<char>>, prev_map: HashMap<(char,char),usize>) -> HashMap<(char,char),usize> {
    let dirs = ['<','^','v','>','A'];

    let mut ends_dir: HashMap<(char,char),usize> = HashMap::new();

    for start in dirs {
        for goals in dirs {
            let prev_pres = dirs_map.get(&(start,goals)).unwrap().clone();
            let mut new_vec: usize = 0;
            let mut cur: char = 'A';
            for next in prev_pres {
                let prev_vec = prev_map.get(&(cur,next)).unwrap();
                new_vec += prev_vec;
                cur = next;
            }
            ends_dir.insert((start,goals),new_vec);
        }
    }

    return ends_dir;
}

// fn sort_dirs_1(a: &char, b: &char) -> Ordering {
//     if *a =='A' && *b == 'A' {
//         return Ordering::Equal;
//     } else if *a == 'A' {
//         return Ordering::Greater;
//     } else if *b == 'A' {
//         return Ordering::Less;
//     } else {
//         return a.cmp(b);
//     }
// }

fn press_keypad(dirs_map: &HashMap<(char,char),usize>) -> HashMap<(char,char),usize> {
    let keys = ['A','0','1','2','3','4','5','6','7','8','9'];
    let dirs = ['<','v','^','>','A'];
    let mut out_map: HashMap<(char,char),usize> = HashMap::new();
    for key in keys {

        let mut heads: VecDeque<(char,Vec<char>)> = VecDeque::new();
        heads.push_back((key, Vec::new()));
        let mut ends: HashMap<char,usize> = HashMap::new();
        while let Some(h) = heads.pop_front() {
            for input in dirs {
                let mut new_vec: Vec<char> = h.1.clone();
                new_vec.push( input );
                
                if input == 'A' {
                    // Calc cost
                    let mut full_vec: usize = 0;
                    let mut cur: char = 'A';
                    for next in new_vec {
                        let prev_vec: usize = *dirs_map.get(&(cur,next)).unwrap();
                        full_vec += prev_vec;
                        cur = next;
                    }

                    if !ends.contains_key(&h.0){
                        ends.insert(h.0, full_vec);
                    } else {
                        let cur_vec = ends.get(&h.0).unwrap();
                        if full_vec < *cur_vec {
                            ends.insert(h.0, full_vec);
                        }
                    }
                } else {
                    let mut vec_clone = new_vec.clone();
                    vec_clone.dedup();
                    if vec_clone.len() > 2 {
                        continue
                    }

                    let new_h = move_keypad(h.0, input);
                    if !new_h.is_none(){
                        heads.push_back((new_h.unwrap(), new_vec));
                    }
                    
                }
            }
        }
        for (k, v) in ends {
            out_map.insert((key,k),v);
        }

    }
    return out_map
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
    
    let mut ans_a: usize = 0;
    let mut ans_b: usize = 0;
    
    let dirs = ['<', '>', 'v', '^', 'A'];
    let mut dirs_map: HashMap<(char,char),Vec<char>> = HashMap::new();
    for d in dirs {
        let ends_d = find_steps_directional(d);
        for (d1, v) in ends_d {
            dirs_map.insert((d,d1), v);
        }
    }


    let mut big_map: HashMap<(char,char),usize> = HashMap::new();
    
    for (k, _v) in &dirs_map {
        big_map.insert(*k,1);
    }


    for i in 0..25 {
        if i == 2 {
            let dists_map = press_keypad(&big_map);
            for line in &lines {
                let mut nbr: usize = 0;
                let mut cur = 'A';
                for c in line.chars() {
                    nbr += dists_map.get(&(cur,c)).unwrap();
                    cur = c;
                }
                //println!("{} - {} - {}",line, nbr, line[..(line.len()-1)].parse::<usize>().unwrap());
                ans_a += nbr * line[..(line.len()-1)].parse::<usize>().unwrap();
            }
        }
        //println!("{}",i);
        big_map = combine_steps(&dirs_map, big_map.clone());
    }
    let key_map = press_keypad(&big_map);

   

    for line in lines {
        let mut nbr: usize = 0;
        let mut cur = 'A';
        for c in line.chars() {
            nbr += key_map.get(&(cur,c)).unwrap();
            cur = c;
        }
        //println!("{} - {} - {}",line, nbr, line[..(line.len()-1)].parse::<usize>().unwrap());
        ans_b += nbr * line[..(line.len()-1)].parse::<usize>().unwrap();
    }

    println!("Answer part A: {}", ans_a);

    println!("Answer part B: {}", ans_b);

    //println!("Num steps tot: {:?}",*route.get(&end_pos).unwrap());

    
    Ok(())
}
