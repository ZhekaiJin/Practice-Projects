# Javascript reading Notes
- [ ] Javascript
- [ ] HTML
- [ ] CSS

**Introduction**

## Template
```javascript
<!DOCTYPE html>
<html>
<body>

<h2>What Can JavaScript Do?</h2>

<p id="demo">JavaScript can change HTML content.</p>

<button type="button" onclick='document.getElementById("demo").innerHTML = "Hello JavaScript!"'>Click Me!</button>

</body>
</html>
```

*JavaScript Can Change HTML Content
```javascript
document.getElementById("demo").innerHTML = "Hello JavaScript";
```
* single quote and double quotes are both supported 
```javascript
document.getElementById('demo').innerHTML = 'Hello JavaScript';
```
*JavaScript Can Change HTML Attributes
```javascript
<button onclick="document.getElementById('myImage').src='pic_bulbon.gif'">Turn on the light</button>

<img id="myImage" src="pic_bulboff.gif" style="width:100px">

<button onclick="document.getElementById('myImage').src='pic_bulboff.gif'">Turn off the light</button>
```
*JavaScript Can Change HTML Styles (CSS)
```javascript
document.getElementById("demo").style.fontSize = "35px";

document.getElementById('demo').style.fontSize = '35px';
```
*JavaScript Can Hide HTML Elements
```javascript
document.getElementById("demo").style.display = "none";
```

*JavaScript Can Show HTML Elements
```javascript
document.getElementById("demo").style.display = "block";
```
