# Notes


## Jonathan Blow algorithm for handling precedence

```python
parse_increasing_precedence(left, min_prec):
    next = gent_next_token()
    if !is_binary_operator(next):
        return left
    next_prec = get_precedence(next)
    if next_prec <= min_prec:
        return left
    else:
        right = parse_expression(next_prec)
        return make_binary(left, to_operator(next), right)

parse_expression(min_prec):
    left = parse_leaf()
    while true:
        node = parse_increasing_precedence(left, min_prec)
        if node == left:
            break
        left = node
    
    return left
```