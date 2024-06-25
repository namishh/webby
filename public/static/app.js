var div = document.createElement("div");

div.innerHTML = `
<ul class="navbar">
<li><a href="/">Home</a></li>
<li><a href="/based">Based</a></li>
<li><a href="/about">About</a></li>
<li><a href="/todos">Todos</a></li>
<li><a href="/rubbish">Does not exist</a></li>
</ul>
`;

document.body.insertBefore(div, document.body.firstChild);
