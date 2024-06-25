const form = document.querySelector('#todo-form');
const todo = document.querySelector('#todo-input');
const priority = document.querySelector('#todo-priority');
const todoList = document.querySelector('#todo-list');


const populateList = async() => {
  todoList.innerHTML = '';
  const res = await fetch('http://localhost:6969/api');
  const text = await res.text()
  const {data} = JSON.parse(text);
  
  let string = '';

  data.forEach((item) => {
    let hex = "#ffffff"
    if (item.priority == 'High') {
      hex = '#ff8787';
    } else if (item.priority == 'Medium') {
      hex = '#ffd8a8';
    }
    string += `<li class="todo-element" data-priorty="${item.priority}" data-id="${item.id}" data-completed="${item.is_completed}">
        <div onclick="req(${item.id}, '${item.task}', '${item.priority}', ${item.is_completed == 0 ? 1 : 0}, 'PUT')"  class="circle" style="background: ${item.is_completed == 0 ? '#444444' : '#bac8ff'}; cursor: pointer; padding: 0.5rem 0.5rem; display: inline; border-radius:100px;"></div>
        <div onclick="req(${item.id}, '${item.task}', '${item.priority}', '${item.is_completed}', 'DELETE')" style="color: #ff8787; cursor: pointer;">X</div>
        <span class="todo-text" style="color: ${hex};">${item.task}</span>
      </li>`;
  });

  todoList.innerHTML = string;
}


form.addEventListener('submit', async function(e) {
  e.preventDefault();
  if (!todo.value) return;
  const res = await fetch('http://localhost:6969/api', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({
      id: Math.floor(Math.random() * 100),
      task: todo.value,
      priority: priority.value,
      is_completed: 0,
    })
  });
  todo.value = '';
  populateList();
});

const req = async(id, v,p,c, m) => {
  const res = await fetch(`http://localhost:6969/api/`, {
    method: m,
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({
      id: id,
      task: v,
      priority: p,
      is_completed: c,
    })
  });
  populateList();
}


populateList();
