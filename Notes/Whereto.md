# Whereto

* JavaScript is the default scripting language in HTML.
* In HTML, JavaScript code must be inserted between <script> and </script> tags.
```javascript
<script>
document.getElementById("demo").innerHTML = "My First JavaScript";
</script>
```
* Functions && Events in ``` <head> or <body> ```
* Placing scripts at the bottom of the <body> element improves the display speed, because script compilation slows down the display.

* External JavaScript
```javascript
<!DOCTYPE html>
<html>
<body> or <head>
<script src="myScript.js"></script>
</body> or </head>
</html>
```
The script will behave as if it was located exactly where the <script> tag is located.
Note:External scripts cannot contain <script> tags.

* External JavaScript Advantages
1.Cached JavaScript files can speed up page loads
2.Readibility 

* External JavaScript references with full URL
```javascript
<script>
<script src="https://www.w3schools.com/js/myScript1.js"></script>
</script>
```

# JavaScript Output
