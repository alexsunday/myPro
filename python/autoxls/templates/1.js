// Generated by CoffeeScript 1.3.1
(function() {
  var onload;

  onload = function() {
    $(".delbutton").click(function() {
      var tr;
      tr = $("table.distbl tr");
      if (tr.length !== 1) {
        return $("table.distbl tr:last").remove();
      }
    });
    $(".addbutton").click(function() {
      var date, html, name, project, week, workcontent, worklength, worktype, workverbose;
      name = $("input.name").val();
      project = $("input.project").val();
      workcontent = $("input.workcontent").val();
      date = $("input.date").val();
      week = $("input.week").val();
      worktype = $("input.worktype").val();
      worklength = $("input.worklength").val();
      workverbose = $("textarea.workverbose").val();
      html = "<tr class='data'>";
      html += "<td>" + name + "</td>";
      html += "<td>" + project + "</td>";
      html += "<td>" + workcontent + "</td>";
      html += "<td>" + date + "</td>";
      html += "<td>" + week + "</td>";
      html += "<td>" + worktype + "</td>";
      html += "<td>" + worklength + "</td>";
      html += "<td>" + workverbose + "</td>";
      html += "</tr>";
      return $("table.distbl").append($(html));
    });
    return $(".submitbutton").click(function() {
      var $td, d, data, i, j, len_tr, str, _i, _j;
      data = {};
      d = [];
      len_tr = $("tr.data").length;
      for (i = _i = 0; 0 <= len_tr ? _i < len_tr : _i > len_tr; i = 0 <= len_tr ? ++_i : --_i) {
        str = "tr.data:eq(" + i + ")";
        $td = $(str).children();
        for (j = _j = 0; _j <= 7; j = ++_j) {
          d[j] = $td[j].innerHTML;
        }
      }
      data[i] = d;
      alert(data);
      return $.post("/admin/", data, function() {
        return alert("Succed!");
      });
    });
  };

  $(onload);

}).call(this);