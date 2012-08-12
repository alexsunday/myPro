onload = ->

	$(".delbutton").click(->
		tr = $("table.distbl tr")
		if tr.length != 1
			$("table.distbl tr:last").remove()
	)

	$(".addbutton").click(->
		name = $("input.name").val()
		project=$("input.project").val()
		workcontent=$("input.workcontent").val()
		date=$("input.date").val()
		week=$("input.week").val()
		worktype=$("input.worktype").val()
		worklength=$("input.worklength").val()
		workverbose=$("textarea.workverbose").val()
		
		html = "<tr class='data'>"
		html += "<td>" + name + "</td>"
		html += "<td>" + project + "</td>"
		html += "<td>" + workcontent + "</td>"
		html += "<td>" + date + "</td>"
		html += "<td>" + week + "</td>"
		html += "<td>" + worktype + "</td>"
		html += "<td>" + worklength + "</td>"
		html += "<td>" + workverbose + "</td>"
		html += "</tr>"
		$("table.distbl").append($(html))
	)
	$(".submitbutton").click(->
		data = {}
		d    = []
		len_tr = $("tr.data").length

		for i in [0...len_tr]
			str = "tr.data:eq(" + i + ")"
			$td = $(str).children()

			for j in [0..7]
				d[j] = $td[j].innerHTML
		data[i] = d
		alert(data)
		$.post("/admin/" , data , ->
			alert("Succed!")
		)
	)

$(onload);
