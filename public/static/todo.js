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
    string += `<li data-priorty="${item.priority}" data-id="${item.id}" data-completed="${item.is_completed}">${item.task}</li>`;
  });

  todoList.innerHTML = string;

  console.log(data);
}


form.addEventListener('submit', async function(e) {
  e.preventDefault();
  const res = await fetch('http://localhost:6969/api', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({
      id: Math.floor(Math.random() * 100),
      task: todo.value,
      priority: priority.value,
      is_completed: "0",
    })
  });
  todo.value = '';
  populateList();
});


populateList();
